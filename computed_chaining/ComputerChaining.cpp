#include "ComputedChaining.h"
#include <iostream> // sil
using namespace std;

ComputedChaining::ComputedChaining(int table_size){
        for (int i = 0; i < table_size; ++i) {
            data_vec.push_back(entry());
        }
}
 int ComputedChaining::hash(int key) {
        return key % data_vec.size();
}
int ComputedChaining::hash2(int key){
        int step=(key/data_vec.size())%data_vec.size();
        if(step==0)step=1;
        return step;
}
void ComputedChaining::insert(int key){
        int index=hash(key);
        
        if(data_vec[index].data != -1){//collision
                if(isThisYourHome(data_vec[index].data)){//Q1: Add to chain
                cout << key << endl;
                        //Your code here
                        int first_index = index;
                        int link_count = 1;
                        int inc = hash2(data_vec[index].data);
                        if(data_vec[index].link == -1){ // hash adressses link is empty
                            index = index += inc;
                            if(index > data_vec.size()-1) index = index - data_vec.size();
                            if(data_vec[index].data == -1) { //first incremented address is empty
                                data_vec[index].data = key;
                                data_vec[first_index].link = link_count;
                            } 
                            else{
                                bool not_insterted = true;
                                while(not_insterted){
                                    link_count++;
                                    index = index += inc;
                                    if(index > data_vec.size()-1) index = index - data_vec.size();
                                    if(data_vec[index].data == -1) { 
                                        data_vec[index].data = key;
                                        data_vec[first_index].link = link_count;
                                        not_insterted = false;
                                    }
                                }
                            }
                        }
                        else{ //hash address link is not empty
                                    vector<int> chain = find_chain(key);
                                    for (int i = 1; i < chain.size(); ++i) {
                                        if(data_vec[chain[i]].link == -1){
                                            inc = hash2(data_vec[ chain[i]].data);
                                            index = chain[i];
                                            first_index = index;
                                            link_count = 0;
                                        }
            
                                    }
                                    
                                bool not_insterted = true;
                                while(not_insterted){
                                    link_count++;
                                    index = index += inc;
                                    if(index > data_vec.size()-1) index = index - data_vec.size();
                                    if(data_vec[index].data == -1) { 
                                        data_vec[index].data = key;
                                        data_vec[first_index].link = link_count;
                                        not_insterted = false;
                                    }
                                }



                }}else{
                    //store the key that will be moved(moved_key)
                    int moved_key = data_vec[index].data;
                    
                    //find the chain of the moved_key
                    vector<int> chain_moved = find_chain(moved_key);
                    
                    //find the index of moved_key in the chain
                    int moved_index = 0;
                    int count = 0;
                    for(int i=0; i<chain_moved.size();i++){
                        if(data_vec[chain_moved[i]].data == moved_key){
                           count++;
                            break;
                        }
                    }
                    moved_index = count;
                    
                    if(moved_index == 0){
                        data_vec[chain_moved[moved_index]].link = -1;
                        data_vec[chain_moved[moved_index]].data = -1;
                    }
                    else{
                        //store the previous index of the moved_key to change the link of the entry
                        data_vec[chain_moved[moved_index - 1]].link = -1;
                    }
                    
                    //store the keys after moved_key in the chain
                    vector<int> keys_after_moved_key;
                    
                    for(int i=moved_index+1; i<chain_moved.size(); i++){
                        keys_after_moved_key.push_back(data_vec[chain_moved[i]].data);
                        data_vec[chain_moved[i]].data = -1;
                        data_vec[chain_moved[i]].link = -1;
                    }
                    
                    //assign -1 to indexes of data_vec where moved_key and remaining -1
                    //insert new key to its original address
                    data_vec[index].data = key;
                    data_vec[index].link= -1; 
                    
                    //insert new key to its original address
                    insert(moved_key);
                    
                    // recursively insert remaining of the chain
                    for(int i=0;i<keys_after_moved_key.size();i++){
                        insert(keys_after_moved_key[i]);
                    }
                        
                }
        }else{//direct insertion
              data_vec[index].data = key;
              data_vec[index].link= -1; 
        }
}
int ComputedChaining::find_index(int key){//find the index of 
        int idx=hash(key);
        int inc=hash2(key);
                if(data_vec[idx].data==key)
                        return idx;
                else{
                        while(data_vec[idx].data != -1){
                                if(data_vec[idx].data != key){
                                        inc=hash2(data_vec[idx].data);
                                        idx=(idx+data_vec[idx].link*inc)%data_vec.size();
                                }else return idx;
                
                }
                }
        return -1;
}
bool ComputedChaining::isThisYourHome(int key){//If returns true if the hash of the key is same with the index of data_vec 
        if(hash(key) == find_index(key)) return true;
        else return false;
}
int ComputedChaining::first_of_my_chain(int key) {
        return data_vec[hash(key)].data;
}

int ComputedChaining::find_num_probes(int key){//
 //Your code here
    int index = hash(key);
    vector<int> chain = find_chain(key);

    if (isThisYourHome(key))
        return 1; // Key is in the hash place, so probe is 1
    else {
        int count = 1;
        for (int i = 0; i < chain.size(); ++i) {
                if(find_index(key) == chain[i]){ break;} // Checks key's chain until that keys index is found
                count++;
            }
            return count;
        }
 

}
vector<int> ComputedChaining::find_chain(int key){ //gives you chain whose member is the key
        vector<int> chain;
        int index=hash(key);
        int inc;//1
        while(data_vec[index].data != -1){
                chain.push_back(index);
                if(data_vec[index].link != -1){
                        inc=hash2(data_vec[index].data);//2
                        index=(index+data_vec[index].link*inc)%data_vec.size();

        }else
                        break;
        }
        return chain;
}
