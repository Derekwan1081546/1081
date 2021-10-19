#include<iostream>
#include<fstream>
#include <iomanip>
#include<vector>
using namespace std;
#define  MAXWORDLENGTH 255
struct record //�إߤ@��struct
{
    char word[MAXWORDLENGTH];
    unsigned int count;
};
int main(int argc, const char* argv[])
{
    ifstream infile("test2.txt", ios::in);  //���}��

    if (!infile)    //�Y������ɮ׫h���X
    {
        cout << "Can not open." << endl;
        return 0;
    }
    ofstream fille("dict.dat", ios::binary | ios::app | ios::out);  //���ؤ@�ӤG����(����X)
    ifstream binaryfile("dict.dat", ios::binary | ios::in); //�A�}�@��(����J)
    vector<record>words;    //�ŧi�@��vector
    int count = 1;  //�ΨӺ�vector�̭����Ʀr���h��
    words.resize(count);    //�T�Osize���j�p
    while (!binaryfile.eof())
    {
        binaryfile.read(reinterpret_cast<char*>(&words[count - 1]), sizeof(words[count - 1]));//��Ū�J���
        count++;
        words.resize(count);
    }
    count--;    //��h�@���h��
    words.pop_back();   //��̫᭱���ťէR��
    binaryfile.close(); //�����ɮ�����
    while (infile >> words[count - 1].word) //�������J
    {
        for (int i = 0; i < MAXWORDLENGTH; i++) //�P�_words�̭����S���ŦX�p�ga~z���d��
        {
            if (words[count - 1].word[i] >= 'A' && words[count - 1].word[i] <= 'Z')
                words[count - 1].word[i] += 32;
            if (words[count - 1].word[i] == '\0')   //�P�_�O�_���Ŧr��
                break;
            if (words[count - 1].word[i] < 'a' || words[count - 1].word[i]>'z') //�P�_�O�_���S��Ÿ�
            {
                for (int j = i + 1; j < MAXWORDLENGTH; j++)
                {
                    words[count - 1].word[j - 1] = words[count - 1].word[j];
                }
                i--;    //�ΨӧP�_�S���p(�p�L�᭱��ӳs��X�{�S��Ÿ�����)
            }
        }

        words[count - 1].count++;   //��ӧO���X�{���Ƴ]��1
        for (int j = 0; j < count - 1; j++) //���Ƨ�
        {
            if (strcmp(words[j].word, words[count - 1].word) == 0)  //�P�_word�̭����r�O�_���ƥX�{
            {
                words[j].count++;   //�X�{����++
                count--;
                words.pop_back();
                break;
            }
        }
        if (words[count - 1].word[0] == '\0')   //�P�_�p�G�Ĥ@�ӼƦr�N�O�Ŧr�����ܴN�R��
        {
            count--;
            words.pop_back();
        }
        count++;    //�A��words�̭������ƥ[�^�h
        words.resize(count);
    }
    count--;
    words.pop_back();

    ofstream outfile("dict.dat", ios::binary | ios::out);   //����X
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
    for (int i = 0; i < words.size(); i++) //�g�J�ɮ�
    {
        outfile.write(reinterpret_cast<char*>(&words[i]), sizeof(words[i]));
        cout << setw(20) << right << words[i].word << " " << words[i].count << endl;
    }
    system("pause");
    return 0;
}