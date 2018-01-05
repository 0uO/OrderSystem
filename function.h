#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include "linker.h"
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>

string RSHash(const char str[]);
int string_to_int(string s);
string int_to_string(int i);
double string_to_double(string s);
string double_to_string(double s);
void get_time(char ch[]);
void write_vec(const char road[],vector<vector<string> > v);

class OrderSystem{
public:
        mysql_connector connector;
        ofstream Guests;
        ofstream Dishs;
        ofstream Waiter;
        ofstream Cooker;
        ofstream Orders;
        ofstream Evalution;

        const int T=20;

        bool check_link(){
            return connector.connect_flag;
        }

        bool connect_to(const char server[],const char user[],const char passwd[],const char database[]){
                connector.connect_to(server,user,passwd,database);
                if(!check_link())
                {
                    int i=T;
                    while(i--){
                        cout<<"Now...Reloading: "<<T-i<<endl;
                        sleep(1);
                        connector.connect_to(server,user,passwd,database);
                        if(check_link())
                            return 1;
                        connector.close();
                    }
                    return 0;
                }
                return 1;
        }

       vector< vector<string> > query(const char q[]){
            connector.query(q);
       }

        bool connect_to(){
                connector.connect_to("111.230.152.243","root","123456babazzzz","OrderSystem");
                if(!check_link())
                {
                    int i=T;
                    while(i--){
                        cout<<"Now...Reloading: "<<T-i<<endl;
                        sleep(2);
                        connector.connect_to("111.230.152.243","root","123456babazzzz","OrderSystem");
                        if(check_link())
                            return 1;
                        connector.close();
                    }
                    return 0;
                }
                return 1;
        }

        void close(){
                connector.close();
        }

        void create_tables(){
                connector.query("CREATE TABLE `Cooker` (`Cno` int NOT NULL ,`Cname` varchar(32) DEFAULT NULL,`Cage` int DEFAULT NULL,`Cgroup` varchar(16) DEFAULT NULL,`OnJob` int NOT NULL, PRIMARY KEY (`Cno`)) ENGINE=InnoDB DEFAULT CHARSET=utf8");
                connector.query("CREATE TABLE `Waiter` (`Wno` int NOT NULL ,`Wname` varchar(32) DEFAULT NULL,`Wage` int DEFAULT NULL,`OnJob` int NOT NULL, PRIMARY KEY (`Wno`)) ENGINE=InnoDB DEFAULT CHARSET=utf8");
                connector.query("CREATE TABLE `Guest` (`Gno` int NOT NULL ,`Passwd` varchar(32) NOT NULL ,`Gname` varchar(32) DEFAULT NULL,`Gage` int DEFAULT NULL,`Cpoint` int DEFAULT NULL, PRIMARY KEY (`Gno`)) ENGINE=InnoDB DEFAULT CHARSET=utf8");

                connector.query("CREATE TABLE `Desk` (`Dno` int NOT NULL ,`Room` varchar(32) DEFAULT NULL,`Dnum` int DEFAULT NULL,`OnJob` int NOT NULL, PRIMARY KEY (`Dno`)) ENGINE=InnoDB DEFAULT CHARSET=utf8");
                connector.query("CREATE TABLE `Dish` (`Dno` int NOT NULL ,`Dprice` double DEFAULT NULL,`Dname` varchar(32) DEFAULT NULL,`Dtype` varchar(16) DEFAULT NULL,`Selling` int NOT NULL, PRIMARY KEY (`Dno`))ENGINE=InnoDB DEFAULT CHARSET=utf8");//, FOREIGN KEY (`Dtype`) REFERENCES `Cooker` (`Cgroup`)

                connector.query("CREATE TABLE `Orders`(`Ono` int NOT NULL, `Deskno` int DEFAULT NULL, `Gno` int DEFAULT NULL, `Time` datetime DEFAULT NULL, `Status` int DEFAULT NULL,`Total` double DEFAULT NULL, PRIMARY KEY(`Ono`), FOREIGN KEY (`Deskno`) REFERENCES `Desk` (`Dno`),FOREIGN KEY (`Gno`) REFERENCES `Guest` (`Gno`))ENGINE=InnoDB DEFAULT CHARSET=utf8");
                connector.query("CREATE TABLE `Orders_now`(`Ono` int NOT NULL, `Dishno` int NOT NULL,`Cno` int DEFAULT NULL,  `num` int NOT NULL,PRIMARY KEY(`Ono`,`Dishno`), FOREIGN KEY (`Dishno`) REFERENCES `Dish` (`Dno`),FOREIGN KEY (`Cno`) REFERENCES `Cooker` (`Cno`))ENGINE=InnoDB DEFAULT CHARSET=utf8");
                connector.query("CREATE TABLE `Orders_done`(`Ono` int NOT NULL, `Dishno` int NOT NULL, `Cno` int DEFAULT NULL, `num` int NOT NULL,PRIMARY KEY(`Ono`,`Dishno`), FOREIGN KEY (`Dishno`) REFERENCES `Dish` (`Dno`),FOREIGN KEY (`Cno`) REFERENCES `Cooker` (`Cno`))ENGINE=InnoDB DEFAULT CHARSET=utf8");
                connector.query("CREATE TABLE `Evalution` (`Gno` int NOT NULL ,`Dno` int NOT NULL,`Time` datetime NOT NULL, `Message` varchar(255), PRIMARY KEY (`Gno`,`Dno`,`Time`),FOREIGN KEY (`Gno`) REFERENCES `Guest` (`Gno`)) ENGINE=InnoDB DEFAULT CHARSET=utf8");

                Guest_reg("123456","root",0);
                connector.query("UPDATE Guest Set Gno=0");
                //connector.query("CREATE TABLE `Making` (`Cno` int NOT NULL ,`Dno` int NOT NULL,`Cgroup` int DEFAULT NULL, PRIMARY KEY (`Cno`,`Dno`),FOREIGN KEY (`Cno`) REFERENCES `Cooker` (`Cno`),FOREIGN KEY (`Dno`) REFERENCES `Dish` (`Dno`)) ENGINE=InnoDB DEFAULT CHARSET=utf8");
                //connector.query("CREATE TABLE `Serving` (`Dno` int NOT NULL ,`Wno` int NOT NULL,`Room` varchar(32) DEFAULT NULL, PRIMARY KEY (`Wno`,`Dno`),FOREIGN KEY (`Wno`) REFERENCES `Waiter` (`Wno`),FOREIGN KEY (`Dno`) REFERENCES `Desk` (`Dno`)) ENGINE=InnoDB DEFAULT CHARSET=utf8");
        }

        void drop_tables(){
                //connector.query("DROP TABLE Making");
                //connector.query("DROP TABLE Serving");
                connector.query("DROP TABLE Evalution");
                connector.query("DROP TABLE Orders_now");
                connector.query("DROP TABLE Orders_done");
                connector.query("DROP TABLE Orders");
                connector.query("DROP TABLE Dish");
                connector.query("DROP TABLE Desk");
                connector.query("DROP TABLE Guest");
                connector.query("DROP TABLE Waiter");
                connector.query("DROP TABLE Cooker");
        }

        void add_record_Cooker(int Cno,const char Cname[],int Cage,const char Cgroup[],int i){
                char q[500];
                sprintf(q,"INSERT INTO Cooker VALUES(%d,'%s',%d,'%s',%d)",Cno,Cname,Cage,Cgroup,i);
                connector.query(q);
        }
        void add_record_Waiter(int Wno,const char Wname[],int Wage,int i){
                char q[500];
                sprintf(q,"INSERT INTO Waiter VALUES(%d,'%s',%d,%d)",Wno,Wname,Wage,i);
                connector.query(q);
        }
        void add_record_Desk(int Dno,int Dnum,const char Room[],int i){
                char q[500];
                sprintf(q,"INSERT INTO Desk VALUES(%d,'%s',%d,%d)",Dno,Room,Dnum,i);
                connector.query(q);
        }
        void add_record_Dish(int Dno,const double Dprice,const char Dname[],const char Dtype[],int i){
                char q[500];
                sprintf(q,"INSERT INTO Dish VALUES(%d,%lf,'%s','%s',%d)",Dno,Dprice,Dname,Dtype,i);
                connector.query(q);
        }
        void add_record_Guest(int Gno,const char Passwd[],const char Gname[],int Gage,int Gpoint){
                char q[500];
                sprintf(q,"INSERT INTO Guest VALUES(%d,'%s','%s',%d,%d)",Gno,Passwd,Gname,Gage,Gpoint);
                connector.query(q);
        }
        void add_record_Orders(int Ono,int Deskno,int Gno,const char Time[],int Status,double Total){
                char q[500];
                sprintf(q,"INSERT INTO Orders VALUES(%d,%d,%d,'%s',%d,%lf)",Ono,Deskno,Gno,Time,Status,Total);
                connector.query(q);

        }
        void add_record_Orders_now(int Ono,int Dishno,int Cno,int num){
                char q[500];
                sprintf(q,"INSERT INTO Orders_now VALUES(%d,%d,%d,%d)",Ono,Dishno,Cno,num);
                connector.query(q);
        }
        void add_record_Orders_done(int Ono,int Dishno,int Cno,int num){
                char q[500];
                sprintf(q,"INSERT INTO Orders_done VALUES(%d,%d,%d,%d)",Ono,Dishno,Cno,num);
                connector.query(q);
        }
        void add_record_Evalution(int Gno,int Dno,const char Time[],const char Message[],int Score){
                char q[500];
                sprintf(q,"INSERT INTO Evalution VALUES(%d,%d,'%s','%s')",Gno,Dno,Time,Message);
                connector.query(q);
        }

        int get_next_num(const char table[], const char column[]){
                char q[200];
                sprintf(q,"SELECT MAX(%s) FROM %s",column,table);
                vector<vector<string> > res = connector.query(q);
                if(res[0][0]=="NULL") return 1;
                return string_to_int(res[0][0])+1;
        }

        int Dname_to_Dno(const char s[]){
                char q[500];
                sprintf(q,"SELECT Dno FROM Dish WHERE Dname='%s'",s);
                vector<vector<string> > res = connector.query(q);
                if(res.size()==0) return -1;
                return string_to_int(res[0][0]);
        }

        string Dno_to_Dname(int Dno){
                char q[500];
                sprintf(q,"SELECT Dno FROM Dish WHERE Dno=%d",Dno);
                vector<vector<string> > res = connector.query(q);
                return res[0][0];
        }

        int get_a_cooker(const char group[]){
                char q[200];
                sprintf(q,"SELECT (Cno) FROM (Cooker) WHERE Cno NOT IN(SELECT Cno FROM Orders_now) AND Cgroup='%s'",group);
                vector<vector<string> > ret = connector.query(q);
                if(ret.size()==0){
                        ret.clear();
                        sprintf(q,"SELECT Cno FROM Orders_now WHERE Cno IN(SELECT Cno FROM Cooker WHERE Cgroup='%s')GROUP BY Cno ORDER BY COUNT(*) ASC LIMIT 1",group);
                        ret = connector.query(q);
                }
                if(ret.size()==0){
                        cout<<"No cooker you loser."<<endl;
                        return -1;
                }
                return string_to_int(ret[0][0]);
        }

        /*
                Under here are the concrete function for application.
        */

        double count_order(vector<string> di,vector<int> num){
            char q[200];
            vector<vector<string> > ret ;
            double total;
            for(int i=0;i<di.size();i++){
                ret.clear();

                sprintf(q,"SELECT Dprice FROM Dish WHERE Dname='%s'",di[i].c_str());
                ret = connector.query(q);
                if(ret.size()==0) continue;//Check if the dish exists
                double price=string_to_double(ret[0][0]);
                total+=num[i]*price;
            }

            return total;
        }

        bool put_orders(int desk, vector<string> di,vector<int> num, int Gno){
                char q[200],ch[64];
                int Ono;
                get_time(ch);
                vector<vector<string> > ret;

//                sprintf(q,"SELECT COUNT(*) FROM Orders WHERE Status=0 AND Deskno='%d'",desk);
//                ret = connector.query(q);
//                if(!(ret[0][0]=="0")){
//                        cout<<"The desk is being used!"<<endl;
//                        return -1;
//                }

                Ono=get_next_num("Orders","Ono");

                for(int i=0;i<di.size();i++){
                    ret.clear();

                    //find the type and Dno
                    sprintf(q,"SELECT Dtype,Dno FROM Dish WHERE Dname='%s'",di[i].c_str());
                    ret = connector.query(q);
                    if(ret.size()==0) continue;//Check if the dish exists
                    char group[16];
                    strncpy(group,ret[0][0].c_str(),16) ;
                    int Dno=string_to_int(ret[0][1]);

                    //find a cooker to cook
                    int Cno=get_a_cooker(group);
                    if(Cno==-1)  return 0;
                    add_record_Orders_now(Ono,Dno,Cno,num[i]);
                }

                add_record_Orders(Ono,desk,Gno,ch,0,count_order(di,num));

                return 1;
        }

        int complete_a_dish(int Ono,const char Dishname[]){
                char q[500];
                sprintf(q,"SELECT Dno FROM Dish WHERE Dname='%s'",Dishname);
                int Dishno = string_to_int(connector.query(q)[0][0]);
                // Check if it's exists
                sprintf(q,"SELECT Cno,num FROM Orders_now WHERE Ono=%d AND Dishno=%d",Ono,Dishno);
                vector<vector<string> > v = connector.query(q);
                if(v.size()==0) return 0;

                // Do
                int Cno=string_to_int(v[0][0]);
                int num=string_to_int(v[0][1]);
                add_record_Orders_done(Ono,Dishno,Cno,num);
                sprintf(q,"DELETE FROM Orders_now WHERE Ono=%d AND Dishno=%d",Ono,Dishno);
                connector.query(q);

                // Check if it's all complete.
                sprintf(q,"SELECT COUNT(*) FROM Orders_now WHERE Ono=%d",Ono);
                v.clear();
                v=connector.query(q);
                if(v[0][0]=="0"){
                    complete_an_order(Ono);
                    return 2;
                }

                return 1;
        }

        void complete_an_order(int Ono){
                char q[200];
                sprintf(q,"UPDATE Orders SET Status=1 WHERE Ono=%d",Ono);
                connector.query(q);
                return ;
        }

        vector<vector<string> > get_all_orders(int Gno){
            char q[200];
            if(Gno!=-1)
                sprintf(q,"SELECT * FROM Orders WHERE Gno=%d",Gno);
            else
                sprintf(q,"SELECT * FROM Orders ");
            vector<vector<string> > res = connector.query(q);
            return res;
        }

        vector<vector<string> > get_all_orders_di(int Ono,int& x){
            char q[200],q2[200];
            if(Ono!=-1){
                sprintf(q,"SELECT Dishno,Cno,num FROM Orders_now WHERE Ono=%d",Ono);
                sprintf(q2,"SELECT Dishno,Cno,num FROM Orders_done WHERE Ono=%d",Ono);
            } else {
                sprintf(q,"SELECT Dishno,Cno,num FROM Orders_now ");
                sprintf(q2,"SELECT Dishno,Cno,num FROM Orders_done ");
            }
            vector<vector<string> > res = connector.query(q);
            vector<vector<string> > res2 =connector.query(q2);
            vector<vector<string> > ans;
            x=res.size();
//            string s="Unfinished";
//            for(int i=0;i<res.size();i++){
//                res[i].push_back(s);
//            }
//            s="Finished";
//            for(int i=0;i<res2.size();i++){
//                res2[i].push_back(s);
//            }

            ans.insert(ans.end(),res.begin(),res.end());
            ans.insert(ans.end(),res2.begin(),res2.end());
            for(int i=0;i<ans.size();i++){
                sprintf(q,"SELECT Dname FROM Dish WHERE Dno=%d ",string_to_int(ans[i][0]));
                ans[i][0]=connector.query(q)[0][0];
            }
            return ans;
        }

        vector<string> get_all_type(){
            char q[300];
            sprintf(q,"SELECT DISTINCT Dtype FROM Dish WHERE Selling=1");
            vector<vector<string> > result = connector.query(q);
            vector<string> ans;
            for(auto i:result){
                for(auto j:i){
                    ans.push_back(j);
                }
            }
            return ans;
        }

        int Guest_reg(const char password[],const char name[],int age){ //Return Gno;
                int Gno=get_next_num("Guest","Gno");

                string s_tmp=RSHash(password);
                char PW[32];
                strncpy(PW,s_tmp.c_str(),32);
                add_record_Guest(Gno,PW,name,age,0);

                return Gno;
        }
        bool Guest_modi(int Gno, const char password[]){ //Return Gno;
                char q[200]="";

                string s_tmp=RSHash(password);
                char PW[32];
                strncpy(PW,s_tmp.c_str(),32);
                cout<<PW<<endl;
                sprintf(q,"UPDATE Guest SET Passwd='%s' WHERE Gno=%d",PW,Gno);
                connector.query(q);

                return 1;
        }

        bool check_login(int Gno,const char passwd[]){//use in login procedure
                char q[500];
                sprintf(q,"SELECT Passwd FROM Guest WHERE Gno=%d",Gno);
                vector<vector<string> > result = connector.query(q);
                if (result.size()!=1) return false;
                return result[0][0] == RSHash(passwd);
        }

        bool add_dish(const char name[],double price,const char type[]){
            int Dno=get_next_num("Dish","Dno");
            char q[200];
            sprintf(q,"SELECT COUNT(*) FROM Dish WHERE Dname='%s'",name);
            if (!(connector.query(q)[0][0]=="0"))
                return 0;
            sprintf(q,"SELECT COUNT(*) FROM Cooker WHERE Cgroup='%s'",type);
            if (connector.query(q)[0][0]=="0")
                return 0;

            add_record_Dish(Dno,price,name,type,1);
            return 1;
        }
        vector<string> get_all_dishes(){
            char q[200];
            sprintf(q,"SELECT Dname FROM Dish WHERE Selling=1");
            vector<vector<string> > result = connector.query(q);
            vector<string> ans;
            for(int i=0;i<result.size();i++){
                ans.push_back(result[i][0]);
            }
            return ans;
        }
        vector<vector<string> > get_part_dishes(string s){
            char q[200];
            sprintf(q,"SELECT Dname,Dprice FROM Dish WHERE Dtype = '%s' AND Selling=1",s.c_str());
            vector<vector<string> > ans = connector.query(q);
            return ans;
        }
        vector<vector<string> > get_part_dishes2(string s){
            char q[200];
            sprintf(q,"SELECT Dno,Dname,Dtype,Dprice FROM Dish WHERE Dtype = '%s' AND Selling=1",s.c_str());
            vector<vector<string> > ans = connector.query(q);
            return ans;
        }
//        void dish_modi(int P){
//            char q[200];
//            sprintf(q,"UPDATE Dish SET Dprice=%d",P);

//        }

        void add_cooker(const char name[], int age,const char group[]){
            int Cno=get_next_num("Cooker","Cno");
            add_record_Cooker(Cno,name, age,group,1);
            return ;
        }
        vector<string> get_all_group(){
            char q[300];
            sprintf(q,"SELECT DISTINCT Cgroup FROM Cooker WHERE OnJob=1");
            vector<vector<string> > result = connector.query(q);
            vector<string> ans;
            for(auto i:result){
                for(auto j:i){
                    ans.push_back(j);
                }
            }
            return ans;
        }
        vector<vector<string> > get_part_cookers(string s){
            char q[200];
            sprintf(q,"SELECT * FROM Cooker WHERE Cgroup='%s' AND OnJob=1",s.c_str());
            vector<vector<string> > ans = connector.query(q);
            return ans;
        }
        vector<string> get_all_cookers(){
            char q[200];
            sprintf(q,"SELECT Cname FROM Cooker WHERE OnJob=1");
            vector<vector<string> > result = connector.query(q);
            vector<string> ans;
            for(int i=0;i<result.size();i++){
                ans.push_back(result[i][0]);
            }
            return ans;
        }

        void add_server(const char name[],int age){
            int Wno=get_next_num("Waiter","Wno");
            add_record_Waiter(Wno,name, age,1);
            return ;
        }
        vector<vector<string> > get_part_servers(string name){
            char q[200];
            sprintf(q,"SELECT * FROM Waiter WHERE Wname='%s' AND OnJob=1",name.c_str());
            vector<vector<string> > ans = connector.query(q);
            return ans;
        }
        vector<string> get_all_waiters(){
            char q[200];
            sprintf(q,"SELECT Wname FROM Waiter WHERE OnJob=1");
            vector<vector<string> > result = connector.query(q);
            vector<string> ans;
            for(int i=0;i<result.size();i++){
                ans.push_back(result[i][0]);
            }
            return ans;
        }

        void add_desk(int num,const char room[]){
            int Dno=get_next_num("Desk","Dno");
            add_record_Desk(Dno,num,room,1);
            return ;
        }
        vector<vector<string> > get_part_desks(string s){
            char q[200];
            sprintf(q,"SELECT * FROM Desk WHERE Room='%s' AND OnJob=1",s.c_str());
            vector<vector<string> > ans = connector.query(q);
            return ans;
        }
        vector<string> get_all_room(){
            char q[300];
            sprintf(q,"SELECT DISTINCT Room FROM Desk WHERE OnJob=1");
            vector<vector<string> > result = connector.query(q);
            vector<string> ans;
            for(auto i:result){
                for(auto j:i){
                    ans.push_back(j);
                }
            }
            return ans;
        }
        vector<string> get_all_desks(){
            char q[200];
            sprintf(q,"SELECT Dno FROM Desk WHERE OnJob=1");
            vector<vector<string> > result = connector.query(q);
            vector<string> ans;
            for(int i=0;i<result.size();i++){
                ans.push_back(result[i][0]);
            }
            return ans;
        }
        int get_a_desk(string room){
            char q[200];
            sprintf(q,"SELECT Dno FROM Desk WHERE OnJob=1 AND Room='%s' ",room.c_str());
            vector<vector<string> > result = connector.query(q);
            int i=rand()%result.size();
            return string_to_int(result[i][0]);
        }

        void add_evalution(int Gno,const char Dname[],const char Message[]){
            char ti[64];
            get_time(ti);
            char q[200];
            sprintf(q,"SELECT Dno FROM Dish WHERE Dname='%s'",Dname);
            int Dno=string_to_int(connector.query(q)[0][0]);
            add_record_Evalution(Gno,Dno,ti,Message,1);
            return ;
        }
        vector<string> get_evalution(const char Dname[],vector<int>& Gno_c){
            char q[200];
            sprintf(q,"SELECT Dno FROM Dish WHERE Dname='%s'",Dname);
            vector<vector<string> > res= connector.query(q);
            int Dno=string_to_int(res[0][0]);
            sprintf(q,"SELECT Message,Gno FROM Evalution WHERE Dno =%d",Dno);
            res.clear();
            res = connector.query(q);
            vector<string> ans;
            for(int i=0;i<res.size();i++){
                ans.push_back(res[i][0]);
                Gno_c.push_back(string_to_int(res[i][1]));
            }
            return ans;
        }

        string get_one(const char table[],const char column[],const char con[],int val){
            char q[200];
            sprintf(q,"SELECT %s FROM %s WHERE %s=%d",column,table,con,val);
            vector<vector<string> > res = connector.query(q);
            return res[0][0];
        }

        bool update_one(vector<string> v,int type){
            char q[200];
            if(type==1)
                sprintf(q,"UPDATE Cooker SET Cname='%s',Cage=%d,Cgroup='%s' WHERE Cno=%d",v[1].c_str(),string_to_int(v[2]),v[3].c_str(),string_to_int(v[0]));
            if(type==2)
                sprintf(q,"UPDATE Waiter SET Wname='%s',Wage=%d WHERE Wno=%d",v[1].c_str(),string_to_int(v[2]),string_to_int(v[0]));
            if(type==3){
                sprintf(q,"SELECT COUNT(*) FROM Dish WHERE Dname='%s'",v[1].c_str());
                if (!(connector.query(q)[0][0]=="0")){
                    sprintf(q,"SELECT Dno FROM Dish WHERE Dname='%s'",v[1].c_str());
                    if(connector.query(q)[0][0]!=v[0])
                        return 0;
                }
                sprintf(q,"SELECT COUNT(*) FROM Cooker WHERE Cgroup='%s'",v[2].c_str());
                if (connector.query(q)[0][0]=="0")
                    return 0;
                sprintf(q,"UPDATE Dish SET Dname='%s',Dtype='%s',Dprice=%lf WHERE Dno=%d",v[1].c_str(),v[2].c_str(),string_to_double(v[3]),string_to_int(v[0]));
            }
                if(type==4)
                sprintf(q,"UPDATE Desk SET Room'%s',Dnum=%d WHERE Cno=%d",v[1].c_str(),string_to_int(v[2]),string_to_int(v[0]));
            connector.query(q);
            return 1;
        }

        void delete_one(int type,int no){
            char q[200];
            string s1,s2,s3;
            if(type==1){
                s1="Cooker";
                s2="Cno";
                s3="OnJob";
            } else if(type==2){
                s1="Waiter";
                s2="Wno";
                s3="OnJob";
            } else if(type==3){
                s1="Dish";
                s2="Dno";
                s3="Selling";
            } else if(type==4){
                s1="Desk";
                s2="Dno";
                s3="OnJob";
            }
            sprintf(q,"SELECT COUNT(*) FROM %s WHERE %s=%d",s1.c_str(),s2.c_str(),no);
            vector<vector<string> > res =connector.query(q);
            if(res[0][0]=="0")return;
            sprintf(q,"UPDATE %s SET %s=0 WHERE %s=%d",s1.c_str(),s3.c_str(),s2.c_str(),no);
            connector.query(q);
        }
};

#endif // FUNCTION_H
