#include<iostream>
#include <string>
#include<fstream>

using namespace std;

class TrieNode {
	public :
	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {
		this -> data = data;
		children = new TrieNode*[26];
		for(int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isTerminal = false;
	}
};

class Trie {
	TrieNode *root;

	public :
	int count;

	Trie() {
		this->count = 0;
		root = new TrieNode('\0');
	}

	bool insertWord(TrieNode *root, string word) {
		// Base case
		if(word.size() == 0) {
			if (!root->isTerminal) {
				root -> isTerminal = true;
				return true;
			} else {
				return false;
			}
		}

		// Small Calculation
		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index] != NULL) {
			child = root -> children[index];
		}
		else {
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}

		// Recursive call
		return insertWord(child, word.substr(1));
	}

	// For user
	void insertWord(string word) {
		if (insertWord(root, word)) {
			this->count++;
		}
	}
    void complete( TrieNode *root, string word, string output, bool &possible, string &key ){
        if( word.length()==0 ){
        	if( root->isTerminal ){
                ///this is first word we found that has key as a prefix
                if( !possible )
                    cout<<"\nWords containing "<<key<<" as prefix are:\n";
                possible = 1;
                cout<<output<<endl;
        	}
            for(int i=0; i<26; i++){
            	if( root->children[i]!=NULL ){
                    string output1 = output;
            	    output1 += root->children[i]->data;
            	    complete( root->children[i], word.substr(), output1, possible, key);
        	    }
        	}
            return;
        }
        int index = word[0] - 'a';
        if( root->children[index]==NULL )
            return;
        else
            complete(root->children[index], word.substr(1), output+word[0], possible, key);
    }

    void autoComplete(string &key, bool &possible) {
        string output = "";
        complete( root, key, output, possible, key);
    }

};

int main()
{
    Trie *t = new Trie();

    ifstream fin;
    string line;
	fin.open("wordlist.txt");

	while( !fin.eof() ){

	   getline(fin,line);
	   t->insertWord(line);

	}

	fin.close();
	bool i=1;
    while(i){
        cout<<"Enter a word to auto-complete it :\n";
        string key;
        cin>>key;
        bool possible=0;
        t->autoComplete( key, possible);

        if( !possible ){
            cout<<"\n\nNo word found with "<<key<<" as prefix\n";
            bool u=1;
            while(u){
                cout<<"Do you wish to add "<<key<<" into the dictionary? \nIf Yes, Press (1) \nIf No, Press(2)\n";
                int s;
                cin>>s;

                if( s == 1 ){
                    ofstream fout;
                    fout.open("wordlist.txt",ios::app);
                    fout<<"\n"<<key;
                    t->insertWord(key);
                    fout.close();
                    cout<<key<<" added to dictionary successfully.\n";
                    u=0;
                }
                else if( s == 2 )
                    u = 0;
                else
                    cout<<"Please Enter a Valid Input! ENTER AGAIN\n";
            }
        }

        int x=1;
        while(x){
            cout<<"\nDo You want to auto-complete something else?\nIf Yes: Press (1) \nIf not: Press (2)\n";
            int ch;
            cin>>ch;

            if (ch==1)
                x=0;
            else if (ch==2){
                x=0;
                i=0;
            }
            else
                cout<<"Please Enter a Valid Input! ENTER AGAIN \n";
        }

    }

}

