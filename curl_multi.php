<?php
/*************************************************************************
 * File Name :    /usr/home/jiamin1/curl.php
 * Author    :    jiamin1
 * Mail      :    jiamin1@staff.sina.com.cn
 ************************************************************************/
    private static function _multi_http_exec($args) {
        if (!extension_loaded('curl')) {
            return self::_error(90400, '服务器没有安装curl扩展！');
        }
        if (empty($args['urls']) || !is_array($args['urls'])) {
            return self::_error(90401, '页面抓取请求url缺失');
        }

        $args['post'] = isset($args['post']) ? $args['post'] : array();
        $args['header'] = isset($args['header']) ? $args['header'] : array();
        $args['timeout'] = isset($args['timeout']) ? $args['timeout'] : self::DAGGER_HTTP_TIMEOUT;
        $args['cookie'] = isset($args['cookie']) ? $args['cookie'] : '';
        $args['redo'] = isset($args['redo']) ? $args['redo'] : self::DAGGER_HTTP_REDO;
        $args['maxredirect'] = isset($args['maxredirect']) ? intval($args['maxredirect']) : self::DAGGER_HTTP_MAXREDIRECT;
        $args['headOnly'] = isset($args['headOnly']) ? $args['headOnly'] : false;
        $args['callback'] = isset($args['callback']) ? $args['callback'] : null;
        $urls = array_filter($args['urls']);
        BaseModelCommon::debug($urls, 'request_multi_urls');

        $ch = curl_init();
        self::_set_curl_opts($ch, $args);

        $header = $ret = $_ch = self::$last_header_info = array();

        //为避免重复请求已经失效的接口，可通过设置mc锁来避免锁有效期内不会再次访问，直接返回上一次的结果
        if(self::$dagger_http_lock_times > 0) {
            // mc锁处理
            $mcd = new BaseModelMemcached('', '', $native = true);
            $mc_http_false_keys = $mc_http_lock_keys = array();
            foreach($urls as $k => $urlinfo) {
                $url = is_array($urlinfo) ? $urlinfo['url'] : $urlinfo;
                $mc_http_key_suffix = md5(($pos = strpos($url, '?')) ? substr($url, 0, $pos) : $url);
                $mc_http_false_keys[$k] = "http_false_" . $mc_http_key_suffix;// 存放最近连续失败累计时间、次数、最后一次正确结果。
                $mc_http_lock_keys[$k] = "http_lock_" . $mc_http_key_suffix;
            }
            $http_lock_values = $mcd->getMultiByKey(self::DAGGER_HTTP_MC_SERVER_KEY, array_unique($mc_http_lock_keys));
        }

        //根据url列表，对返回结果进行初始化为false，同时根据mc锁情况，决定需要初始化哪些curl句柄
        foreach($urls as $k => $urlinfo) {
            $ret[$k] = false;   //此处初始化所有返回结果为false的目的，是避免在发生超时等异常情况时，后续逻辑中curl_multi_info_read有时在超时下返回false而不是result=28(Timout)的数组，导致最终返回结果中，丢失了相应url的结果值(false)
            if(self::$dagger_http_lock_times > 0) {
                // mc锁处理
                if(is_array($http_lock_values) && isset($http_lock_values[$mc_http_lock_keys[$k]])) {
                    $url = is_array($urlinfo) ? $urlinfo['url'] : $urlinfo;
                    BaseModelCommon::debug('接口[' . $url . ']在10秒内出现'. self::$dagger_http_lock_times .'次错误，锁定30秒返回false', 'request_multi_warn');
                    self::_error(90403, "请求连续" . self::$dagger_http_lock_times ." 次失败[{$url}]");
                    self::$last_header_info[$k] = $header[$k] = $ret[$k] = false;
                    continue;
                }
            }
            $_ch[$k] = curl_copy_handle($ch);
            if(is_array($urlinfo)) {
                //== multi时，不同请求的私有化参数设置 ==//
                self::_set_curl_opts($_ch[$k], $urlinfo, $first = false);
                // url
                curl_setopt($_ch[$k], CURLOPT_URL, $urlinfo['url']);
            } else {
                curl_setopt($_ch[$k], CURLOPT_URL, $urlinfo);
            }
            if(!isset($mh)) {
                $mh = curl_multi_init();
            }
            curl_multi_add_handle($mh, $_ch[$k]);
            BaseModelCommon::addStatInfo('request');
        }


        if(isset($mh)) {
            $startRunTime = microtime(true);
            //curl_multi_exec主循环
            do {
                $redoUrls = array();
                do {
                    $mrc = curl_multi_exec($mh, $active);
                } while ($mrc === CURLM_CALL_MULTI_PERFORM);

                while($active && $mrc === CURLM_OK) {
                    //启用select阻塞来避免cpu 100%
                    if(curl_multi_select($mh) == -1)
                    {
                        ;
                    }

                    do {
                        $mrc = curl_multi_exec($mh, $active);
                    } while ($mrc == CURLM_CALL_MULTI_PERFORM);

                    //这里需要注意，如果发生了超时等异常情况，curl_multi_info_read函数有时会返回一个result=28(Timeout)的结果，有时直接返回false，也就是说该判断里关于超时的剩余逻辑将有可能不会被执行
                    if($mhinfo = curl_multi_info_read($mh)) {
                        $k = array_search($mhinfo['handle'], $_ch);

                        if($mhinfo['result'] === CURLE_OK) {
                            $ret[$k] = curl_multi_getcontent($mhinfo['handle']);
                            $code = curl_getinfo($mhinfo['handle'], CURLINFO_HTTP_CODE);

                            // $chinfo = curl_getinfo($mhinfo['handle']);
                            if (in_array($code, array(301, 302, 303, 307), true)) {
                                $redirect[$k] = empty($redirect[$k]) ? 1 : ++$redirect[$k];
                                if($redirect[$k] > $args['maxredirect']) {
                                    $msg = "redirect larger than {$maxredirect} [{$k}][{$urls[$k]['url']}]";
                                    BaseModelCommon::debug($msg , 'request_redirect_warn');
                                    self::_error(90406, $msg);
                                } else {
                                    BaseModelCommon::debug("redirect times:{$redirect[$k]},url:{$urls[$k]['url']}", 'request_redirect_info');
                                    preg_match('/Location:(.*?)\n/i', $ret[$k], $matches);
                                    $newurl = trim($matches[1]);
                                    if($newurl{0} === '/') {
                                        preg_match("@^([^/]+://[^/]+)/@", curl_getinfo($mhinfo['handle'], CURLINFO_EFFECTIVE_URL), $matches);
                                        $newurl = $matches[1] . $newurl;
                                    }
                                    $redoUrls[$k] = $urls[$k];
                                    $redoUrls[$k]['url'] = $newurl;
                                    BaseModelCommon::debug("[{$k}][old]{$urls[$k]['url']}[new]{$newurl}", 'request_redirect_url');
                                }
                            } else if($code !== 200) {
                                $msg = "http code unnormal : [{$code}] [{$k}][{$urls[$k]['url']}]";
                                BaseModelCommon::debug($msg, 'request_http_warn');
                                self::_error(90405, $msg);
                            }

                            if(strpos($ret[$k], "\r\n\r\n") !== false) {
                                if(empty($args['callback'])) {
                                    list($header[$k], $ret[$k]) = explode("\r\n\r\n", $ret[$k], 2);
                                    self::$last_header_info[$k] = $header[$k];
                                    // 抓取header时，解析header头
                                    if($args['headOnly']) {
                                        $ret[$k] = self::_parse_header($header[$k]);
                                    }
                                } else {
                                    call_user_func($args['callback'], $k, $ret[$k]);
                                }
                            } else {
                                $header[$k] = $ret[$k] = false;
                                empty($args['callback']) || call_user_func($args['callback'], $k, $ret[$k]);
                            }

                            if(in_array($code, array(403,404), true)) {
                                $ret[$k] = false;
                            }
                        } else {
                            $redo[$k] = empty($redo[$k]) ? 1 : ++$redo[$k];
                            if($redo[$k] <= $args['redo']) {
                                $redoUrls[$k] = $urls[$k];
                            } else {
                                self::$last_header_info[$k] = $header[$k] = $ret[$k] = false;
                                is_callable($args['callback']) && call_user_func($args['callback'], $k, $ret[$k]);
                            }
                            $curl_error = curl_error($mhinfo['handle']);
                            BaseModelCommon::debug("[errno] {$mhinfo['result']} [error] {$curl_error}",'request_curl_error');
                            self::_error(90404, "curl内部错误信息[{$mhinfo['result']}][{$curl_error}][{$urls[$k]['url']}]");
                        }
                        curl_multi_remove_handle($mh, $mhinfo['handle']);
                        curl_close($mhinfo['handle']);
                    }
                };

                // 添加需要再次请求的句柄，包括redirect和redo
                if(!empty($redoUrls)) {
                    BaseModelCommon::debug($redoUrls, 'request_redoUrl_info');
                    foreach($redoUrls as $k => $urlinfo) {
                        $_chs = curl_copy_handle($ch);
                        curl_setopt($_chs, CURLOPT_URL, $urlinfo['url']);
                        $_ch[$k] = $_chs;
                        curl_multi_add_handle($mh, $_ch[$k]);
                        BaseModelCommon::addStatInfo('request');
                    }
                }
            } while(!empty($redoUrls));

            curl_multi_close($mh);
            $runTime = BaseModelCommon::addStatInfo('request', $startRunTime, 0);

            // mc缓存处理
            if(self::$dagger_http_lock_times > 0) {
                foreach($ret as $k => $_r) {
                    if($_r === false) {
                        // 10秒钟内连续失败20次，30秒钟锁定，直接返回false;
                        if (!$mcd->addByKey(self::DAGGER_HTTP_MC_SERVER_KEY, $mc_http_false_keys[$k], 1, 10)) {
                            $falseCount = $mcd->incrementByKey(self::DAGGER_HTTP_MC_SERVER_KEY, $mc_http_false_keys[$k], 1, 1);
                            if ($falseCount > self::$dagger_http_lock_times - 1) {
                                $mcd->addByKey(self::DAGGER_HTTP_MC_SERVER_KEY, $mc_http_lock_keys[$k], 1, 30);
                            }
                        }
                    } else {
                        $mcd->deleteMultiByKey(self::DAGGER_HTTP_MC_SERVER_KEY, array($mc_http_false_keys[$k], $mc_http_lock_keys[$k]));
                    }
                }
            }

            // 生成调试信息
            if (defined('DAGGER_DEBUG') && 1 === DAGGER_DEBUG) {
                $d = array();
                foreach($ret as $k => $v) {
                    is_string($v) && ($len = strlen($v)) > 2000 && $v = (substr($v, 0, 2000) . '......超长('.$len.')，截取2000字节');
                    $d[$k] = array($k, $urls[$k]['url'], $v);
                }
                asort($d);
                array_unshift($d, array('序号', '请求地址', '执行结果'));
                $d[] = array('', '运行时间', $runTime);
                BaseModelCommon::debug($d, 'request_multi_return');
            }
        }

        return $ret;
    }
?>
