#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// p[i][j][k] is the probability from state i to state j with observation k 
// val[t] gives t(th) observation;

int int_map(string phone){
	if (phone=="AA") return 0;
	if (phone=="AE") return 1;
	if (phone=="AH") return 2;
	if (phone=="AO") return 3;
	if (phone=="AW") return 4;
	if (phone=="AY") return 5;
	if (phone=="B") return 6;
	if (phone=="CH") return 7;
	if (phone=="D") return 8;
	if (phone=="DH") return 9;
	if (phone=="EH") return 10;
	if (phone=="ER") return 11;
	if (phone=="EY") return 12;
	if (phone=="F") return 13;
	if (phone=="G") return 14;
	if (phone=="HH") return 15;
	if (phone=="IH") return 16;
	if (phone=="IY") return 17;
	if (phone=="JH") return 18;
	if (phone=="K") return 19;
	if (phone=="L") return 20;
	if (phone=="M") return 21;
	if (phone=="N") return 22;
	if (phone=="NG") return 23;
	if (phone=="OW") return 24;
	if (phone=="OY") return 25;
	if (phone=="P") return 26;
	if (phone=="R") return 27;
	if (phone=="S") return 28;
	if (phone=="SH") return 29;
	if (phone=="T") return 30;
	if (phone=="TH") return 31;
	if (phone=="UH") return 32;
	if (phone=="UW") return 33;
	if (phone=="V") return 34;
	if (phone=="W") return 35;
	if (phone=="Y") return 36;
	if (phone=="Z") return 37;
	if (phone=="ZH") return 38;
	if (phone=="SIL") return 39;
	if (phone==".") return 40;
}
string phone_map(int i){
    if (i == 0) return "AA";
    if (i == 1) return "AE";
    if (i == 2) return "AH";
    if (i == 3) return "AO";
    if (i == 4) return "AW";
    if (i == 5) return "AY";
    if (i == 6) return "B";
    if (i == 7) return "CH";
    if (i == 8) return "D";
    if (i == 9) return "DH";
    if (i == 10) return "EH";
    if (i == 11) return "ER";
    if (i == 12) return "EY";
    if (i == 13) return "F";
    if (i == 14) return "G";
    if (i == 15) return "HH";
    if (i == 16) return "IH";
    if (i == 17) return "IY";
    if (i == 18) return "JH";
    if (i == 19) return "K";
    if (i == 20) return "L";
    if (i == 21) return "M";
    if (i == 22) return "N";
    if (i == 23) return "NG";
    if (i == 24) return "OW";
    if (i == 25) return "OY";
    if (i == 26) return "P";
    if (i == 27) return "R";
    if (i == 28) return "S";
    if (i == 29) return "SH";
    if (i == 30) return "T";
    if (i == 31) return "TH";
    if (i == 32) return "UH";
    if (i == 33) return "UW";
    if (i == 34) return "V";
    if (i == 35) return "W";
    if (i == 36) return "Y";
    if (i == 37) return "Z";
    if (i == 38) return "ZH";
    if (i == 39) return "SIL";
    if (i == 40) return ".";
}

string str_toupper(string s){
	locale loc;
	string ans = "";
	for (int i=0; i< s.size(); i++){
		ans += toupper(s[i], loc);
	}
	return ans;
}

int main(){
	
	double p[41][41][26];
	for (int i=0; i< 41; i++){
		for (int j=0; j< 41; j++){
			for (int k=0; k< 26; k++){
				p[i][j][k] = 0.0;
			}
		}
	}

	ifstream file("temp/training_data.dat", ios::in);

	while(1){
		string p1,p2;
		char g;
		double prob;
		file>>p1;
		if (p1 == "--") break;
		file>>p2>>g>>prob;
		int temp1 = int_map(p1);
		int temp2 = int_map(p2);
		int temp3 = g - 'A';
		p[temp1][temp2][temp3] = prob;
	}

	double seqscore[41][20];
	for(int i=0; i<41; i++){
		for(int j=0; j<20; j++) seqscore[i][j]=0.0;
	}

	ifstream probfile("temp/initial_probabilities.dat", ios::in);

	while(true){
		string s;
		probfile >> s;
		if(s=="--")break;
		else{
			double initprob;
			probfile >> initprob;
			
			seqscore[int_map(s)][0] = initprob;
		}
	}

	while(true){
		string val;
		cin >> val;	// graphene
		if (val == "-") break;
		val = str_toupper(val);
		val = val + ".";
		int t = val.length();
		
		double backptr[41][t];
		
		for(int z=1; z<t; z++){
			for(int q=0; q<41; q++){
				double maxnum = 0;
				int bestindex = 0;
				for(int r=0; r<41; r++){

					if(maxnum < seqscore[r][z-1]*p[r][q][val[z-1]-'A']){
						maxnum = seqscore[r][z-1]*p[r][q][val[z-1]-'A'];
						bestindex = r;
					}
					
				}
				seqscore[q][z] = maxnum;
				backptr[q][z] = bestindex;

			}
		}
		int laststate = 0;
		int bestscore = seqscore[0][t-1];
		for(int i=1; i<41; i++){
			
			if(seqscore[i][t-1] > bestscore){
				laststate = i;
			}
		}
		int c[t];
		c[t-1] = laststate;
		for(int i=t-2; i>=0; i--)c[i] = backptr[c[i+1]][i+1];
		for(int i=0; i<t-2; i++) cout << phone_map(c[i]) << " ";
			cout<<phone_map(c[t-2])<<endl;
	}

	return 0;
	
}
