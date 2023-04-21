import re
import time

import requests
import weibo_db


class WeiboSpider:
    def __init__(self):
        # self.__cookies = {}
        # self.__headers = {
        #     'Accept': 'application/json, text/plain, */*',
        #     'Accept-Encoding': 'gzip, deflate, sdch',
        #     'Accept-Language': 'zh-CN,zh;q=0.8,en;q=0.6,ja;q=0.4,zh-TW;q=0.2,mt;q=0.2',
        #     'Connection': 'keep-alive',
        #     'Host': 'm.weibo.cn',
        #     'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
        #                   'Chrome/74.0.3729.169 Safari/537.36',
        #     'X-Requested-With': 'XMLHttpRequest',
        # }
        self.__user_url = 'https://m.weibo.cn/api/container/getIndex?uid={uid}&type=uid&value={uid}&containerid=100505{uid}'
        self.__follow_url = 'https://m.weibo.cn/api/container/getIndex?containerid=231051_-_followers_-_{uid}&page={page}'
        self.__fan_url = 'https://m.weibo.cn/api/container/getIndex?containerid=231051_-_fans_-_{uid}&since_id={page}'
        self.__weibo_url = 'https://m.weibo.cn/api/container/getIndex?uid={uid}&type=uid&page={page}&containerid=107603{uid}'
        self.__comment_url = 'https://m.weibo.cn/api/comments/show?id={weibo_id}&page={page}'
        self.__crawled_uid_set = set()

        try:
            # 连接mysql数据库
            self.__db_helper = weibo_db.DbHelper()
            # self.__db_helper.create_all_table()
        except Exception as e:
            print(e.args)
            return

        for item in self.__db_helper.get_crawled_uid():
            self.__crawled_uid_set.add(item[0])

    # 爬这几个url不需要登录
    # def login(self, username, password):
    #     try:
    #         browser = webdriver.Chrome(r"C:\Users\Administrator\Downloads\chromedriver.exe")
    #         browser.implicitly_wait(5)
    #         browser.get('https://passport.weibo.cn/signin/login')
    #
    #         wait = WebDriverWait(browser, 10)
    #         username_input = wait.until(EC.presence_of_element_located((By.ID, 'loginName')))
    #         username_input.send_keys(username)
    #         password_input = wait.until(EC.presence_of_element_located((By.ID, 'loginPassword')))
    #         password_input.send_keys(password)
    #         # TODO:判断是否有验证码
    #         login_button = wait.until(EC.element_to_be_clickable((By.ID, 'loginAction')))
    #         login_button.click()
    #         print('正在登录...')
    #         try:
    #             wait.until(EC.title_is('微博'))
    #         except TimeoutException as e:
    #             print('用户名或密码错误!')
    #             return False
    #     except Exception as e:
    #         print(e.args)
    #         return False
    #     else:
    #         print('登录成功!')
    #         cookies = browser.get_cookies()
    #         cookie_list = []
    #         # for dict in cookies:
    #         #    cookie = dict['name'] + '=' + dict['value']
    #         #    cookie_list.append(cookie)
    #
    #         # self.__cookies['Cookies'] = ';'.join(cookie_list)
    #         self.__cookies.clear()
    #         for dict in cookies:
    #             self.__cookies[dict['name']] = dict['value']
    #         print(self.__cookies)
    #         return True
    def crawl_follow_list(self, uid, limit=None):
        """uid:要爬取关注列表的用户uid limit:最大爬取数量,None代表爬取全部"""
        print('开始爬取用户{}的关注列表'.format(uid))
        page = 1
        index = 0
        while True:
            try:
                while True:
                    time.sleep(0.2)
                    response = requests.get(self.__follow_url.format(uid=uid, page=page))
                    # if response.status_code != 200:
                    if response.text != '':
                        break
                    else:
                        # 请求太快会返回418
                        print('请求发生错误 三秒后重试...')
                        time.sleep(3)
                result = response.json()
                if not result.get('ok'):
                    print('爬取结束 共爬了{}页'.format(page - 1))
                    break
                if result.get('data').get('cards')[-1].get('card_group'):
                    follows = result.get('data').get('cards')[-1].get('card_group')
                    for follow in follows:
                        follow_uid = follow.get('user').get('id')
                        follow_relation = weibo_db.FollowRelation(uid, follow_uid, index + 1)
                        print(uid, follow_uid)
                        self.__db_helper.save_to_follow_relation_table(follow_relation)
                        index += 1
                        if limit and index > limit:
                            return None
                page += 1
            except Exception as e:
                print(e.args)
        print('用户{}的关注列表爬取完毕'.format(uid))

    def crawl_sec_level_follow_list(self, uid, limit=None):
        for item in self.__db_helper.get_follow_uid(uid):
            self.crawl_follow_list(item[0], limit)

    def crawl_fans_list(self, uid, limit=None):
        print('开始爬取用户{}的粉丝列表'.format(uid))
        page = 1
        index = 0
        while True:
            try:
                while True:
                    time.sleep(3)
                    response = requests.get(self.__fan_url.format(uid=uid, page=page))
                    # if response.status_code != 200:
                    if response.text != '':
                        break
                    else:
                        # 请求太快会返回418
                        print('请求发生错误 三秒后重试...')
                        time.sleep(3)
                result = response.json()
                if not result.get('ok'):
                    if limit and index < limit:
                        print('请求发生错误 10秒后重试...')
                        time.sleep(10)
                        continue
                    print('爬取结束 共爬了{}页'.format(page - 1))
                    break
                if result.get('data').get('cards')[-1].get('card_group'):
                    fans_list = result.get('data').get('cards')[-1].get('card_group')
                    for fans in fans_list:
                        fans_uid = fans.get('user').get('id')
                        fans_relation = weibo_db.FansRelation(uid, fans_uid, index + 1)
                        self.__db_helper.save_to_fans_relation_table(fans_relation)
                        print(uid, fans_uid)
                        index += 1
                        if limit and index > limit:
                            return None
                page += 1
            except Exception as e:
                print(e.args)
        print('用户{}的粉丝列表爬取完毕'.format(uid))

    def crawl_self_info(self, uid):
        self.crawl_user_info(uid)

    def crawl_follows_info(self, uid):
        print('开始爬取{}的关注用户的信息'.format(uid))
        for item in self.__db_helper.get_follow_uid(uid):
            self.crawl_user_info(item[0])
        print('{}的关注用户的信息爬取完毕'.format(uid))

    def crawl_fans_info(self, uid):
        print('开始爬取{}的粉丝信息'.format(uid))
        for item in self.__db_helper.get_fans_uid(uid):
            self.crawl_user_info(item[0])
        print('{}的粉丝信息爬取完毕'.format(uid))

    def crawl_user_info(self, uid):
        if uid in self.__crawled_uid_set:
            print('跳过重复爬取的用户')
            return
        try:
            while True:
                while True:
                    time.sleep(2)
                    response = requests.get(self.__user_url.format(uid=uid))
                    # if response.status_code != 200:
                    if response.text != '':
                        break
                    else:
                        # 请求太快会返回418
                        print('请求发生错误 120秒后重试...')
                        time.sleep(120)
                result = response.json()
                if result.get('ok'):
                    user_info = result.get('data').get('userInfo')

                    uid = user_info.get('id')
                    name = user_info.get('screen_name')
                    gender = user_info.get('gender')
                    verified = user_info.get('verified')
                    verified_reason = ['', user_info.get('verified_reason')][verified]
                    urank = user_info.get('urank')
                    mbrank = user_info.get('mbrank')
                    weibos_count = user_info.get('statuses_count')
                    fans_count = user_info.get('followers_count')
                    follows_count = user_info.get('follow_count')
                    description = user_info.get('description')

                    user = weibo_db.User(uid, name, gender, verified, verified_reason, urank, mbrank, weibos_count,
                                         fans_count,
                                         follows_count,
                                         description)
                    self.__db_helper.save_to_user_table(user)
                    self.__crawled_uid_set.add(uid)

                    print('uid:' + uid.__repr__(), '用户名:' + name, '性别:' + gender, '简介:' + description)
                    break
                else:
                    print('请求发生错误 10秒后重试...')
                    time.sleep(10)
                    continue
        except Exception as e:
            print(e.args)

    def crawl_weibo(self, uid, limit=None):
        print('开始爬取{}的微博'.format(uid))
        page = 1
        index = 0
        while True:
            try:
                while True:
                    time.sleep(2)
                    response = requests.get(self.__weibo_url.format(uid=uid, page=page))
                    # if response.status_code != 200:
                    if response.text != '':
                        break
                    else:
                        # 请求太快会返回418
                        print('请求发生错误 三秒后重试...')
                        time.sleep(3)
                result = response.json()
                if not result.get('ok'):
                    if limit and index < limit:
                        print('请求发生错误 10秒后重试...')
                        time.sleep(10)
                        continue
                    print('爬取结束 共爬了{}页'.format(page - 1))
                    break

                weibos = result.get('data').get('cards')

                for weibo in weibos:
                    mblog = weibo.get('mblog')
                    if mblog:
                        weibo_id = mblog.get('id')
                        attitudes_count = mblog.get('attitudes_count')
                        comments_count = mblog.get('comments_count')
                        reposts_count = mblog.get('reposts_count')
                        created_at = mblog.get('created_at')
                        created_at = self.__fix_time_format(created_at)
                        source = mblog.get('source')
                        text = mblog.get('text')

                        weibo = weibo_db.Weibo(uid, weibo_id, attitudes_count, comments_count, reposts_count,
                                               created_at,
                                               source, text, index + 1
                                               )
                        self.__db_helper.save_to_weibo_table(weibo)
                        print(weibo_id, attitudes_count, comments_count, reposts_count, created_at, source, text)
                        index += 1
                        if limit and index > limit:
                            return None
                page += 1
            except Exception as e:
                print(e.args)
        print('爬取{}的微博完毕'.format(uid))

    def __fix_time_format(self, created_at):
        if re.match('刚刚', created_at):
            created_at = time.strftime('%Y-%m-%d', time.localtime(time.time()))
        if re.match('\d+分钟前', created_at):
            minute = re.match('(\d+)', created_at).group(1)
            created_at = time.strftime('%Y-%m-%d',
                                       time.localtime(time.time() - float(minute) * 60))
        if re.match('\d+小时前', created_at):
            hour = re.match('(\d+)', created_at).group(1)
            created_at = time.strftime('%Y-%m-%d',
                                       time.localtime(time.time() - float(hour) * 60 * 60))
        if re.match('昨天.*', created_at):
            created_at = time.strftime('%Y-%m-%d', time.localtime(time.time() - 24 * 60 * 60))
        if re.match('\d{2}-\d{2}', created_at):
            created_at = time.strftime('%Y-', time.localtime()) + created_at

        return created_at


if __name__ == '__main__':
    uid = '2376916624'
    weiboSpider = WeiboSpider()
    weiboSpider.crawl_self_info(uid)
    weiboSpider.crawl_follow_list(uid, 1000)
    weiboSpider.crawl_fans_list(uid, 10000)
    weiboSpider.crawl_follows_info(uid)
    weiboSpider.crawl_fans_info(uid)
    weiboSpider.crawl_weibo(uid, 2000)
    weiboSpider.crawl_sec_level_follow_list(uid, 1000)
    input('按任意键结束...')
