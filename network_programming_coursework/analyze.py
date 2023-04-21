import matplotlib
import pymysql
import numpy as np
import matplotlib.pyplot as plt

from py2neo import Graph, Node, Relationship

matplotlib.rcParams['font.sans-serif'] = ['SimHei']
matplotlib.rcParams['axes.unicode_minus'] = False


class Analyze:
    def __init__(self):
        # 连接mysql数据库
        self.__conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', passwd='123', db='weibo',
                                      charset='utf8')
        print('mysql连接成功')
        # 连接neo4j数据库
        self.__graph = Graph('http://localhost:7474', username='neo4j', password='123')
        print('neo4j连接成功')
        # self.__graph.delete_all()

    def create_neo4j_node(self, uid):
        sql1 = 'SELECT * FROM user_table WHERE user_table.uid = {}'.format(uid)
        sql2 = '''
            SELECT
            user_table.uid,
            user_table.`name`,
            user_table.gender,
            user_table.verified,
            user_table.verified_reason,
            user_table.urank,
            user_table.mbrank,
            user_table.weibos_count,
            user_table.fans_count,
            user_table.follows_count,
            user_table.description
            FROM
            user_table ,
            follow_relation_table
            WHERE
            follow_relation_table.uid = {} AND
            follow_relation_table.follow_id = user_table.uid
        '''.format(uid)
        try:
            with self.__conn.cursor() as cursor:
                cursor.execute(sql1)
                user = cursor.fetchone()
                self.__graph.create(Node('User', uid=user[0], name=user[1], gender=user[2], verified=user[3],
                                         verified_reason=user[4], urank=user[5], mbrank=user[6],
                                         weibos_count=user[7], fans_count=user[8], follows_count=user[9],
                                         description=user[10]))
                cursor.execute(sql2)
                for item in cursor:
                    self.__graph.create(Node('User', uid=item[0], name=item[1], gender=item[2], verified=item[3],
                                             verified_reason=item[4], urank=item[5], mbrank=item[6],
                                             weibos_count=item[7], fans_count=item[8], follows_count=item[9],
                                             description=item[10]))
                print('neo4j节点创建成功')

        except Exception as e:
            print(e.args)

    def create_neo4j_relation(self):
        try:
            with self.__conn.cursor() as cursor:
                cursor.execute('SELECT * FROM follow_relation_table')
                for item in cursor:
                    node1 = self.__graph.nodes.match("User", uid=item[0]).first()
                    node2 = self.__graph.nodes.match("User", uid=item[1]).first()
                    if node1 and node2:
                        self.__graph.create(Relationship(node1, 'follow', node2, order=item[2]))
                print('neo4j关系创建成功')

        except Exception as e:
            print(e.args)

    def analyz_follow_sex_ratio(self):
        sql = '''SELECT
                    user_table.gender,count(user_table.gender)
                    FROM
                    follow_relation_table ,
                    user_table
                    WHERE
                    follow_relation_table.uid = 2376916624 AND
                    follow_relation_table.follow_id = user_table.uid
                    GROUP BY
                    user_table.gender'''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            dic = {}
            for item in cursor:
                dic[item[0]] = item[1]
            self.draw_pie(['男', '女'], [dic['m'], dic['f']], [0.05, 0], '江西师范大学官方微博关注用户的男女比例')

    def analyz_fans_sex_ratio(self):
        sql = '''SELECT
                    user_table.gender,count(user_table.gender)
                    FROM
                    fans_relation_table ,
                    user_table
                    WHERE
                    fans_relation_table.uid = 2376916624 AND
                    fans_relation_table.fans_id = user_table.uid
                    GROUP BY
                    user_table.gender'''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            dic = {}
            for item in cursor:
                dic[item[0]] = item[1]
            self.draw_pie(['男', '女'], [dic['m'], dic['f']], [0.05, 0], '江西师范大学官方微博粉丝的男女比例')

    def analyz_fans_urank_distribution(self):
        sql = '''
                SELECT
                user_table.urank,count(user_table.urank)
                FROM
                fans_relation_table ,
                user_table
                WHERE
                fans_relation_table.uid = 2376916624 AND
                fans_relation_table.fans_id = user_table.uid
                GROUP BY
                user_table.urank
            '''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            li = [0, 0, 0, 0, 0]
            for item in cursor:
                if 0 <= item[0] < 10:
                    li[0] += item[1]
                elif 10 <= item[0] < 20:
                    li[1] += item[1]
                elif 20 <= item[0] < 30:
                    li[2] += item[1]
                elif 30 <= item[0] < 40:
                    li[3] += item[1]
                elif 40 <= item[0] <= 48:
                    li[4] += item[1]
            self.draw_bar(['0-9级', '10-19级', '20-19级', '30-39级', '40-48级'], li, '人数', '江西师范大学官方微博粉丝的用户等级分布')

    def analyz_fans_mbrank_distribution(self):
        sql = '''
                SELECT
                user_table.mbrank,count(user_table.mbrank)
                FROM
                fans_relation_table ,
                user_table
                WHERE
                fans_relation_table.uid = 2376916624 AND
                fans_relation_table.fans_id = user_table.uid
                GROUP BY
                user_table.mbrank
            '''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            li = [0, 0, 0, 0, 0, 0, 0]
            for item in cursor:
                li[item[0]] += item[1]
            self.draw_bar(['0级', '1级', '2级', '3级', '4级', '5级', '6级'], li, '人数', '江西师范大学官方微博粉丝的会员等级分布')

    def analyz_follows_urank_distribution(self):
        sql = '''
                SELECT
                user_table.urank,count(user_table.urank)
                FROM
                follow_relation_table ,
                user_table
                WHERE
                follow_relation_table.uid = 2376916624 AND
                follow_relation_table.follow_id = user_table.uid
                GROUP BY
                user_table.urank
            '''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            li = [0, 0, 0, 0, 0]
            for item in cursor:
                if 0 <= item[0] < 10:
                    li[0] += item[1]
                elif 10 <= item[0] < 20:
                    li[1] += item[1]
                elif 20 <= item[0] < 30:
                    li[2] += item[1]
                elif 30 <= item[0] < 40:
                    li[3] += item[1]
                elif 40 <= item[0] <= 48:
                    li[4] += item[1]
            self.draw_bar(['0-9级', '10-19级', '20-19级', '30-39级', '40-48级'], li, '人数', '江西师范大学官方微博关注的用户等级分布')

    def analyz_follows_mbrank_distribution(self):
        sql = '''
                SELECT
                user_table.mbrank,count(user_table.mbrank)
                FROM
                follow_relation_table ,
                user_table
                WHERE
                follow_relation_table.uid = 2376916624 AND
                follow_relation_table.follow_id = user_table.uid
                GROUP BY
                user_table.mbrank
            '''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            li = [0, 0, 0, 0, 0, 0, 0, 0]
            for item in cursor:
                li[item[0]] += item[1]
            print(li)
            self.draw_bar(['0级', '1级', '2级', '3级', '4级', '5级', '6级', '7级'], li, '人数', '江西师范大学官方微博关注用户的会员等级分布')

    def analyz_fans_verified_ratio(self):
        sql = '''SELECT
                    user_table.verified,count(user_table.verified)
                    FROM
                    fans_relation_table ,
                    user_table
                    WHERE
                    fans_relation_table.uid = 2376916624 AND
                    fans_relation_table.fans_id = user_table.uid
                    GROUP BY
                    user_table.verified'''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            dic = {}
            for item in cursor:
                dic[item[0]] = item[1]
            self.draw_pie(['未认证', '已认证'], [dic['0'], dic['1']], [0.05, 0], '江西师范大学官方微博粉丝的认证比例')

    def analyz_follows_verified_ratio(self):
        sql = '''SELECT
                    user_table.verified,count(user_table.verified)
                    FROM
                    follow_relation_table ,
                    user_table
                    WHERE
                    follow_relation_table.uid = 2376916624 AND
                    follow_relation_table.follow_id = user_table.uid
                    GROUP BY
                    user_table.verified'''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            dic = {}
            for item in cursor:
                dic[item[0]] = item[1]
            self.draw_pie(['未认证', '已认证'], [dic['0'], dic['1']], [0.05, 0], '江西师范大学官方微博关注用户的认证比例')

    def analyz_weibo_post_tendency(self):
        sql = '''
                SELECT
                weibo_table.created_at,
                count(weibo_table.created_at)
                FROM
                weibo_table
                WHERE
                weibo_table.uid = 2376916624
                GROUP BY
                weibo_table.created_at
            '''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            x = ['2018-10', '2018-11', '2018-12', '2019-01', '2019-02', '2019-03', '2019-04', '2019-05', '2019-06']
            y = [0, 0, 0, 0, 0, 0, 0, 0, 0]
            dic = dict(zip(x, y))
            for item in cursor:
                dic[item[0][:7]] += item[1]
            xticks, heights = [], []
            print(dic)
            for k, v in dic.items():
                xticks.append(k)
                heights.append(v)

            self.draw_plot(xticks, heights, '发布总数', '江西师范大学官方微博每月发布微博数变化趋势图')

    def analyz_weibo_source(self):
        sql = '''SELECT
                    weibo_table.source,
                    count(weibo_table.source)
                    FROM
                    weibo_table
                    WHERE
                    weibo_table.uid = 2376916624
                    GROUP BY
                    weibo_table.source
                    HAVING
                    source!=''
                    ORDER BY COUNT(weibo_table.source) DESC
                    LIMIT 10'''
        with self.__conn.cursor() as cursor:
            cursor.execute(sql)
            results = cursor.fetchall()
            source_list = []
            count_list = []
            for source, count in results:
                source_list.append(source)
                count_list.append(count)

            name_list = source_list
            num_list = count_list
            plt.barh(range(len(num_list)), num_list, color='rgb', tick_label=name_list)
            plt.title('使用次数排名前10的发布微博设备')
            plt.show()

    def draw_pie(self, labels, sizes, explode, title):
        plt.pie(sizes, labels=labels, autopct='%1.1f%%', shadow=True, explode=explode, startangle=50)
        plt.axis('equal')
        plt.title(title)
        plt.show()

    def draw_bar(self, xticks, heights, ylabel, title):
        plt.bar(range(len(heights)), heights, align='center', color='steelblue', alpha=0.8)
        plt.ylabel(ylabel)
        plt.title(title)
        plt.xticks(range(len(xticks)), xticks)
        for x, y in enumerate(heights):
            plt.text(x, y, '%s' % round(y, 1), ha='center')
        plt.show()

    def draw_plot(self, xticks, heights, ylabel, title):
        plt.plot(xticks, heights)
        plt.ylabel(ylabel)
        plt.title(title)
        plt.show()


if __name__ == '__main__':
    analyze = Analyze()
    analyze.create_neo4j_node('2376916624')
    analyze.create_neo4j_relation()
    # analyze.draw_pie(['A', 'B'], [2, 3], [0.05, 0], 'test')
    # analyze.analyz_follow_sex_ratio()
    # analyze.analyz_fans_sex_ratio()
    # analyze.analyz_fans_urank_distribution()
    # analyze.analyz_fans_mbrank_distribution()
    # analyze.analyz_follows_urank_distribution()
    # analyze.analyz_follows_mbrank_distribution()
    # analyze.analyz_fans_verified_ratio()
    # analyze.analyz_follows_verified_ratio()
    # analyze.analyz_weibo_source()
    # analyze.analyz_weibo_post_tendency()
