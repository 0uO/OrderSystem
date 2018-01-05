#ifndef LINKER_H
#define LINKER_H

#include <string.h>
#include <vector>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <regex>

using namespace std;

struct mysql_connector{
        char server[32];
        char user[32];
        char passwd[32];
        char database[32];
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        bool connect_flag;
        regex e1;
        regex e2;


        mysql_connector(const char server[],const char user[],const char passwd[],const char database[]){
                connect_flag = true;
                strcpy(this->server,server);
                strcpy(this->user,user);
                strcpy(this->passwd,passwd);
                strcpy(this->database,database);

                conn = mysql_init(NULL);

                if (!mysql_real_connect(conn,server,user,passwd,database,0,NULL,CLIENT_MULTI_RESULTS)){
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        connect_flag = false;
                }
        }
        mysql_connector(){
            regex e1 ="(.*)(or( *)('\\w+'|'?\\d+'?)( *)=( *)('\\w+'|'?\\d+'?))(.*)";
            regex e2 ="(SELECT|DROP|DELETE|UPDATE|INSERT)(.*)(([Ss][Ee][Ll][Ee][Cc][Tt])|([Dd][Rr][Oo][pP])|([Dd][Ee][Ll][Ee][Tt][Ee])|([Uu][Pp][Dd][Aa][Tt][Ee])|([Ii][nN][sS][Ee][Rr][Tt]))(.*)";


        }
        void close(){
                mysql_close(conn);
        }

        void connect_to(const char server[],const char user[],const char passwd[],const char database[]){
                connect_flag = true;
                strcpy(this->server,server);
                strcpy(this->user,user);
                strcpy(this->passwd,passwd);
                strcpy(this->database,database);

                conn = mysql_init(NULL);

                if (!mysql_real_connect(conn,server,user,passwd,database,0,NULL,CLIENT_MULTI_RESULTS)){
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        connect_flag = false;
                }
        }

        vector< vector<string> > query(const char q[]){
            connect_flag = true;
            cout<<q<<endl;
            string s=q;

            if(regex_match(s,e1) || regex_match(s,e2)){
                printf("What do you want to do!\n");
                connect_flag = false;
                close();
                exit(1);
            }
                vector< vector<string> > result;
                if (conn == NULL){
                        printf("Cannot conncet to database!\n");
                        connect_flag = false;
                        close();
                }
                for(int i=0;i<10;i++){
                    if (mysql_query(conn,q)){
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            connect_flag = false;
                    } else break;
                }
                if(connect_flag == false)
                    return result;
                res = mysql_use_result(conn);
                if (res == NULL) return result;

                while ((row = mysql_fetch_row(res)) != NULL){
                        vector<string> tmprow;
                        int fields_num = mysql_num_fields(res);
                        for (int i = 0;i<fields_num;i++){
                            if (row[i]!=NULL) tmprow.push_back(row[i]);
                            else tmprow.push_back("NULL");
                        }
                        result.push_back(tmprow);
                }
                mysql_free_result(res);
                return result;
        }
};

#endif // LINKER_H
