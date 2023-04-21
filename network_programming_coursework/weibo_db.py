import pymysql


class DbHelper:

    def __init__(self):
        self.create_user_table_sql = '''
            CREATE TABLE `user_table` (
              `uid` varchar(255) NOT NULL,
              `name` varchar(255) NOT NULL,
              `gender` varchar(255) NOT NULL,
              `verified` varchar(255) NOT NULL,
              `verified_reason` varchar(255) DEFAULT NULL,
              `urank` int(11) NOT NULL,
              `mbrank` int(11) NOT NULL,
              `weibos_count` int(11) NOT NULL,
              `fans_count` int(11) NOT NULL,
              `follows_count` int(11) NOT NULL,
              `description` varchar(255) DEFAULT NULL,
              PRIMARY KEY (`uid`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
            '''
        self.create_follow_relation_table_sql = '''
            CREATE TABLE `follow_relation_table` (
              `uid` varchar(255) NOT NULL,
              `follow_id` varchar(255) NOT NULL,
              PRIMARY KEY (`uid`,`follow_id`) USING BTREE
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
            '''
        self.create_fans_relation_table_sql = '''
            CREATE TABLE `fans_relation_table` (
              `uid` varchar(255) NOT NULL,
              `fans_id` varchar(255) NOT NULL,
              PRIMARY KEY (`uid`,`fans_id`) USING BTREE
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
            '''
        self.create_weibo_table_sql = '''
            CREATE TABLE `weibo_table` (
              `weibo_id` varchar(255) NOT NULL,
              `uid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
              `attitudes_count` varchar(255) NOT NULL,
              `comments_count` varchar(255) NOT NULL,
              `reposts_count` varchar(255) NOT NULL,
              `created_at` varchar(255) NOT NULL,
              `source` varchar(255) DEFAULT NULL,
              `text` varchar(8196) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
              PRIMARY KEY (`weibo_id`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
            '''
        self.create_comments_table_sql = '''
            CREATE TABLE `comments_table` (
              `comment_id` varchar(255) NOT NULL,
              `uid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
              `weibo_id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
              `created_at` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
              `source` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
              `text` varchar(1024) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
              `like_counts` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
              PRIMARY KEY (`comment_id`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
            '''

        self.insert_user_table_sql = '''
            INSERT INTO `weibo`.`user_table`(`uid`, `name`, `gender`, `verified`, 
            `verified_reason`, `urank`, `mbrank`, `weibos_count`, `fans_count`, `follows_count`, `description`) VALUES (
            %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s); 
            '''
        self.insert_follow_relation_table_sql = '''
            INSERT INTO `weibo`.`follow_relation_table`(`uid`, `follow_id`, `order`) VALUES (%s, %s, %s);
            '''
        self.insert_fans_relation_table_sql = '''
            INSERT INTO `weibo`.`fans_relation_table`(`uid`, `fans_id`, `order`) VALUES (%s, %s, %s);
            '''
        self.insert_weibo_table_sql = '''
            INSERT INTO `weibo`.`weibo_table`(`weibo_id`, `uid`, `attitudes_count`, 
            `comments_count`, `reposts_count`, `created_at`, `source`, `text`, `order`) VALUES (%s, %s, %s, %s, %s, 
            %s, %s, %s, %s); 
            '''
        self.insert_comments_table_sql = '''
            INSERT INTO `weibo`.`comments_table`(`comment_id`, `uid`, `weibo_id`, 
            `created_at`, `source`, `text`, `like_counts`, `order`) VALUES (%s, %s, %s, %s, %s, %s, %s, %s); 
            '''

        self.conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', passwd='123', db='weibo', charset='utf8')
        print('mysql连接成功')

    def __del__(self):
        self.conn.close()

    def create_all_table(self):
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(DbHelper.create_user_table_sql)
                cursor.execute(DbHelper.create_follow_relation_table_sql)
                cursor.execute(DbHelper.create_fans_relation_table_sql)
                cursor.execute(DbHelper.create_weibo_table_sql)
                cursor.execute(DbHelper.create_comments_table_sql)
            print('所有创建表成功')
        except Exception as e:
            print(e.args)

    def save_to_user_table(self, user):
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(self.insert_user_table_sql, (
                    user.uid, user.name, user.gender, user.verified, user.verified_reason,
                    user.urank, user.mbrank, user.weibos_count,
                    user.fans_count, user.follows_count, user.description
                ))
                self.conn.commit()
        except Exception as e:
            print(e.args)

    def save_to_weibo_table(self, weibo):
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(self.insert_weibo_table_sql, (
                    weibo.weibo_id, weibo.uid, weibo.attitudes_count, weibo.comments_count, weibo.reposts_count,
                    weibo.created_at, weibo.source, weibo.text, weibo.order
                ))
                self.conn.commit()
        except Exception as e:
            print(e.args)

    def save_to_follow_relation_table(self, follow_relation):
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(self.insert_follow_relation_table_sql,
                               (follow_relation.uid, follow_relation.follow, follow_relation.order))
                self.conn.commit()
        except Exception as e:
            print(e.args)

    def save_to_fans_relation_table(self, fans_relation):
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(self.insert_fans_relation_table_sql,
                               (fans_relation.uid, fans_relation.fans, fans_relation.order))
                self.conn.commit()
        except Exception as e:
            print(e.args)

    def save_to_comments_table(self, comment):
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(self.insert_comments_table_sql, (
                    comment.comment_id, comment.uid, comment.weibo_id, comment.created_at, comment.source, comment.text,
                    comment.like_counts, comment.order))
                self.conn.commit()
        except Exception as e:
            print(e.args)

    def get_fans_uid(self, uid):
        select_sql = '''SELECT DISTINCT
                        fans_relation_table.fans_id
                        FROM
                        fans_relation_table
                        WHERE
                        fans_relation_table.uid = %s
                    '''
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(select_sql, uid)
                yield from cursor.fetchall()
        except Exception as e:
            print(e.args)

    def get_follow_uid(self, uid):
        select_sql = '''SELECT DISTINCT
                        follow_relation_table.follow_id
                        FROM
                        follow_relation_table
                        WHERE
                        follow_relation_table.uid = %s
                    '''
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(select_sql, uid)
                yield from cursor.fetchall()
        except Exception as e:
            print(e.args)

    def get_crawled_uid(self):
        select_sql = '''SELECT
                        user_table.uid
                        FROM
                        user_table
                    '''
        try:
            with self.conn.cursor() as cursor:
                cursor.execute(select_sql)
                yield from cursor.fetchall()
        except Exception as e:
            print(e.args)


class User:
    def __init__(self, uid, name, gender, verified, verified_reason, urank, mbrank, weibos_count, fans_count,
                 follows_count, description):
        self.uid = uid
        self.name = name
        self.gender = gender
        self.verified = verified
        self.verified_reason = verified_reason
        self.urank = urank
        self.mbrank = mbrank
        self.weibos_count = weibos_count
        self.fans_count = fans_count
        self.follows_count = follows_count
        self.description = description


class FollowRelation:
    def __init__(self, uid, follow, order):
        self.uid = uid
        self.follow = follow
        self.order = order


class FansRelation:
    def __init__(self, uid, fans, order):
        self.uid = uid
        self.fans = fans
        self.order = order


class Weibo:
    def __init__(self, uid, weibo_id, attitudes_count, comments_count, reposts_count, created_at, source, text, order):
        self.uid = uid
        self.weibo_id = weibo_id
        self.attitudes_count = attitudes_count
        self.comments_count = comments_count
        self.reposts_count = reposts_count
        self.created_at = created_at
        self.source = source
        self.text = text
        self.order = order


class Comment:
    def __init__(self, uid, weibo_id, comment_id, created_at, source, text, like_counts, order):
        self.uid = uid
        self.weibo_id = weibo_id
        self.comment_id = comment_id
        self.created_at = created_at
        self.source = source
        self.text = text
        self.like_counts = like_counts
        self.order = order
