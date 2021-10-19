#include<iostream>
#include<fstream>
#include <iomanip>
#include<vector>
using namespace std;
#define  MAXWORDLENGTH 255
struct record //建立一個struct
{
    char word[MAXWORDLENGTH];
    unsigned int count;
};
int main(int argc, const char* argv[])
{
    ifstream infile("test2.txt", ios::in);  //先開檔

    if (!infile)    //若未找到檔案則跳出
    {
        cout << "Can not open." << endl;
        return 0;
    }
    ofstream fille("dict.dat", ios::binary | ios::app | ios::out);  //先建一個二元檔(做輸出)
    ifstream binaryfile("dict.dat", ios::binary | ios::in); //再開一次(做輸入)
    vector<record>words;    //宣告一個vector
    int count = 1;  //用來算vector裡面的數字有多少
    words.resize(count);    //確保size的大小
    while (!binaryfile.eof())
    {
        binaryfile.read(reinterpret_cast<char*>(&words[count - 1]), sizeof(words[count - 1]));//先讀入資料
        count++;
        words.resize(count);
    }
    count--;    //把多一項去掉
    words.pop_back();   //把最後面的空白刪掉
    binaryfile.close(); //先把檔案關掉
    while (infile >> words[count - 1].word) //當把測資丟入
    {
        for (int i = 0; i < MAXWORDLENGTH; i++) //判斷words裡面有沒有符合小寫a~z的範圍
        {
            if (words[count - 1].word[i] >= 'A' && words[count - 1].word[i] <= 'Z')
                words[count - 1].word[i] += 32;
            if (words[count - 1].word[i] == '\0')   //判斷是否為空字元
                break;
            if (words[count - 1].word[i] < 'a' || words[count - 1].word[i]>'z') //判斷是否為特殊符號
            {
                for (int j = i + 1; j < MAXWORDLENGTH; j++)
                {
                    words[count - 1].word[j - 1] = words[count - 1].word[j];
                }
                i--;    //用來判斷特殊情況(如過後面兩個連續出現特殊符號的話)
            }
        }

        words[count - 1].count++;   //把個別的出現次數設為1
        for (int j = 0; j < count - 1; j++) //做排序
        {
            if (strcmp(words[j].word, words[count - 1].word) == 0)  //判斷word裡面的字是否重複出現
            {
                words[j].count++;   //出現次數++
                count--;
                words.pop_back();
                break;
            }
        }
        if (words[count - 1].word[0] == '\0')   //判斷如果第一個數字就是空字元的話就刪掉
        {
            count--;
            words.pop_back();
        }
        count++;    //再把words裡面的次數加回去
        words.resize(count);
    }
    count--;
    words.pop_back();

    ofstream outfile("dict.dat", ios::binary | ios::out);   //做輸出
    for (int i = 0; i < words.size(); i++)  //bubble sort
    {
        for (int j = i + 1; j < words.size(); j++)
        {
            if (words[i].count < words[j].count)
            {
                record buffer = words[j];
                words[j] = words[i];
                words[i] = buffer;
            }
        }
    }
    for (int i = 0; i < words.size(); i++) //寫入檔案
    {
        outfile.write(reinterpret_cast<char*>(&words[i]), sizeof(words[i]));
        cout << setw(20) << right << words[i].word << " " << words[i].count << endl;
    }
    system("pause");
    return 0;
}