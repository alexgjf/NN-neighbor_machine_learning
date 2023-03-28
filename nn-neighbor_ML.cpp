#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>

using namespace std;

void printSet(vector<int> v)
{
	for(int i = 0; i<v.size(); i++)
	{
		cout<<v[i];
		if(i+1<v.size()) cout<<",";
	}
}

float euclidean(vector<float> v1, vector<float> v2)
{
	float total = 0;
	for(int i = 1; i<v1.size(); i++)
	{
		total = total + pow((v1[i]-v2[i]), 2);
	}
	return sqrt(total);
}

float findAccuracy(vector<vector<float> > dataset,vector<int> curset, int f)
{
	for(int a = 1; a<dataset[0].size(); a++)
	{
		if(find(curset.begin(),curset.end(), a)==curset.end() and a!=f)
		{
			for(int b = 0; b<dataset.size(); b++)
			{
				dataset[b][a]=0;
			}
		}
	}
	//Calculate accuracuy of each instance of each features and store it in a vector
	int numcc = 0;
	for(int j = 0; j<dataset.size(); j++)
	{
		float nearest_d = 100;
		int nearest_n = INT_MAX;
		int label = dataset[j][0];
		int nearest_l;
		vector<float> curr = dataset[j];
		for(int k = 0; k<dataset.size(); k++)
		{
			if(k!=j)
			{
				float distance = euclidean(curr, dataset[k]);
				
				if(distance<nearest_d)
				{
					nearest_d = distance;
					nearest_n = k;
					nearest_l = dataset[nearest_n][0];
				}
			}
		}	
		//cout<<"Object "<<j<<" is class "<<label<<". Its closest n is "<<nearest_n<<" which is in class "<<nearest_l<<endl;
		if(label == nearest_l) numcc++;
	}
	float accuracy = numcc / float(dataset.size());
	//cout<<numcc<<" "<<dataset.size()<<" "<<accuracy<<endl;
	return accuracy;
}



void Forward(vector<vector<float> > dataset){
	float m=0;
	int bigf;
	float temp, globalmax=0;
	vector<int> visited;
	int feature;
	cout<<dataset.size()<<endl;
	
	for(int j = 1; j<dataset.size() ; j++)
	{
		m=0;
		for(int i = 1; i<dataset[0].size() ; i++)
		{
			if(find(visited.begin(), visited.end(), i)==visited.end())
			{
				
				temp = findAccuracy(dataset,visited, i);
				m=max(m,temp);
				if(m == temp) bigf = i;
				cout<<"Using feature(s) {"<<i<<"} accuracy is "<< temp*100 <<"%\n";
				
			}	
		}
		globalmax = max(globalmax,m);
		
		cout<<endl;
		
		if(m<globalmax) {
			cout<<"(Warning, accuracy has decreased!)\n";
			break;
		}
		
		visited.push_back(bigf);
		
		cout<<"Feature set {";
		for(int i = visited.size(); i>0; i--)
		{
			cout<<visited[i-1];
			if(i>1) cout<<",";
		}
		cout<<"} was best, accuracy is "<<m*100<<"%\n\n";
		
		
	}
	
	cout<<"Finished search!! The best feature sebset is {";
	for(int i = visited.size(); i>0; i--)
	{
		cout<<visited[i-1];
		if(i>1) cout<<",";
	}
	cout<<"}, which has an accuracy of "<< globalmax*100<<"%\n";
	for(int i = 0; i<visited.size(); i++) 
	{
		cout<<visited[i]<<endl;
	}
//	cout<<"\n\n here: ";
//	for(int i=0; i<dataset.size(); i++)
//	{
//		cout<<dataset[i][6]<<endl;
//	}
//	cout<<"\n\n here: ";
//	for(int i=0; i<dataset.size(); i++)
//	{
//		cout<<dataset[i][0]<<endl;
//	}
//	cout<<"\n\n here: ";
//	for(int i=0; i<dataset.size(); i++)
//	{
//		cout<<dataset[i][2]<<endl;
//	}
}

void Backward(vector<vector<float> > dataset){
	float m=0;
	int bigf;
	float temp, globalmax=0;
	vector<int> feature;
	
	for(int i = 1; i<dataset[0].size(); i++)
	{
		feature.push_back(i);
	}
	
	temp = findAccuracy(dataset, feature, 0);
	cout<<"Using feature(s) {";
	printSet(feature);
	cout<<"} accuracy is "<< temp*100 <<"%\n\n";
	
	for(int j = 1; j<dataset.size() ; j++)
	{
		vector<int> localm;
		m=0;
		for(int i = 1; i<feature.size()+1 ; i++)
		{
			vector<int> tv;
			if(true)
			{
				tv.clear();
				copy(feature.begin(), feature.end(), back_inserter(tv)); 
				tv.erase(tv.begin()+i-1);
				
				temp = findAccuracy(dataset,tv, 0);

				
				if(m<max(m,temp)) 
				{
					m=max(m,temp);
					localm.clear();
					copy(tv.begin(), tv.end(), back_inserter(localm));
					bigf = i;
				}
				
				cout<<"Using feature(s) {";
				
				for(int k = 0; k<tv.size(); k++)
				{
					cout<<tv[k];
					if(k<tv.size()-1) cout<<",";
				}
				
				cout<<"} accuracy is "<< temp*100 <<"%\n";
			}
		}
		feature.clear();
		copy(localm.begin(), localm.end(), back_inserter(feature));
		globalmax = max(globalmax,m);
		
		cout<<endl;
		
		if(m<globalmax) {
			cout<<"(Warning, accuracy has decreased!)\n";
			break;
		}
		
		cout<<"Feature set {";
		for(int i = feature.size(); i>0; i--)
		{
			cout<<feature[i-1];
			if(i>1) cout<<",";
		}
		cout<<"} was best, accuracy is "<<m*100<<"%\n\n";
		
		
	}
	
	cout<<"Finished search!! The best feature sebset is {";
	for(int i = feature.size(); i>0; i--)
	{
		cout<<feature[i-1];
		if(i>1) cout<<",";
	}
	cout<<"}, which has an accuracy of "<< globalmax*100<<"%\n";
	for(int i = 0; i<feature.size(); i++) 
	{
		cout<<feature[i]<<endl;
	}
}

int main() {
	int feature, choice;
	
//Select and store dataset into a 2D vector
	cout<<"Select a data set, 1 for small data set, 2 for large data set: \n";
	cin >> choice;
	string filename;
	if(choice==1)
	{
		filename = "Small_data__30.txt";
	}else
	{
		filename = "Large_data__30.txt";
	}
	ifstream ReadFile(filename);
    vector<vector<float> > data;
    int count = 0;
    string line;
   	while(getline(ReadFile, line))
   	{
   		vector<float> v;
   		stringstream lineStream(line);
		   
		float value;
		while(lineStream >> value)
		{
			v.push_back(value);
		}
		data.push_back(v);
	}

	cout<<"Type the number of the algorithm you want to run.\n\n";
	
	cout<<"\t 1) Forward Selection\n\t 2) Backward Elimination\n\t 3) Special Alogrithm\n";
	
	cin>>choice;
	
	cout<<"Beginning search.\n\n";
	
	if(choice == 1)
	{
		Forward(data);
	}
	else if (choice == 2)
	{
		Backward(data);
	}
//	else{
//		Special(data);
//	}
	
	return 0;
}