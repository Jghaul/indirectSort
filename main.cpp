#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <windows.h>

using namespace std;

double get_cpu_time() {
	FILETIME a, b, c, d;
	if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0) {
		unsigned long long kernel = c.dwLowDateTime | ((unsigned long long)c.dwHighDateTime << 32);
		unsigned long long user   = d.dwLowDateTime | ((unsigned long long)d.dwHighDateTime << 32);
		return (double)(kernel + user) * 0.0000001;
	}
	else { return 0; } // TODO: Handle error
}
template <typename Comparable,typename T>
void merge(std::vector<Comparable> & grades,std::vector<T> & names, std::vector<Comparable> & tmpArray, std::vector<T> & tmpArray2, size_t leftPos, size_t rightPos, size_t rightEnd)
{
	size_t leftEnd = rightPos - 1;
	size_t tmpPos = leftPos;
	size_t numElements = rightEnd - leftPos + 1;
	//std::vector<Comparable> tmpArray2(a.size());


	// Main loop
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (grades[leftPos] <= grades[rightPos])
		{
            tmpArray2[tmpPos] = std::move(names[leftPos]);
			tmpArray[tmpPos++] = std::move(grades[leftPos++]);



		}
		else
		{
		    tmpArray2[tmpPos] = std::move(names[rightPos]);
			tmpArray[tmpPos++] = std::move(grades[rightPos++]);

		}
	}
	while (leftPos <= leftEnd) // Copy rest of first half
	{
	    tmpArray2[tmpPos] = std::move(names[leftPos]);
		tmpArray[tmpPos++] = std::move(grades[leftPos++]);

	}
	while (rightPos <= rightEnd) // Copy rest of right half
	{
	    tmpArray2[tmpPos] = std::move(names[rightPos]);
		tmpArray[tmpPos++] = std::move(grades[rightPos++]);

	}

	// Copy tmpArray back
	for (size_t i = 0; i < numElements; ++i, --rightEnd) {
        grades[rightEnd] = std::move(tmpArray[rightEnd]);

        names[rightEnd] = std::move(tmpArray2[rightEnd]);
	}
}

template <class Comparable, typename T>
void insertionSort(std::vector<Comparable> & grades,std::vector<T> & names, size_t left, size_t right)
{
	for (size_t i = left+1; i <= right; ++i)
	{
		Comparable temp = std::move(grades[i]);
		T temp2 = std::move(names[i]);
		size_t j;
		for (j = i; j > left && temp < grades[j - 1]; --j){
			grades[j] = std::move(grades[j - 1]);
			names[j] = std::move(names[j - 1]);

		}
		names[j] = std::move(temp2);
        grades[j] = std::move(temp);


	}
}
template <typename Comparable, typename T>
void timSort(std::vector<Comparable> & grades,std::vector<T> & names, std::vector<Comparable> & tmpArray, std::vector<T> & tmpArray2, size_t left, size_t right)
{
	if (left  < right)
	{
		size_t center = (left + right) / 2;
		timSort(grades,names, tmpArray, tmpArray2, left, center);
		timSort(grades,names, tmpArray, tmpArray2, center + 1, right);
		merge(grades,names, tmpArray, tmpArray2, left, center + 1, right);
	}
	else
	{
		insertionSort(grades,names, left, right);
	}
}
    template <typename Comparable, typename T>
void timSort(std::vector<Comparable> & grades, std::vector<T> & names)
{

	std::vector<Comparable> tmpArray(grades.size());
	std::vector<T> tmpArray2(names.size());
	timSort(grades,names, tmpArray, tmpArray2, 0, grades.size() - 1);

}


int main()
{

    vector <string> names;
    vector <double> grades;

    string words;
    cout<<"Enter the name file."<<endl;

    string input;
    cin>>input;
    ifstream textFile(input.c_str());

    double numbers;
    cout<<"Enter the data file."<<endl;
    string input2;
    cin>>input2;
    ifstream textFile2(input2.c_str());


while(textFile >> words){

    names.push_back(words);

}
while(textFile2 >> numbers){

    grades.push_back(numbers);

}







double begin=get_cpu_time();
for(int i = 0;i<1000;i++)
{
  timSort(grades,names);
}

double end = get_cpu_time();

double elapsedSecs = end-begin/1000;



cout<<"Time running: "<<elapsedSecs<<endl;

for(int i = 0;i<names.size();i++){
cout<<names[i]<<": ";
cout<<grades[i]<<endl;

}
cout<<"names size: "<<names.size()<<endl;

cout<<"grades size: "<<grades.size()<<endl;
}
/*
ofstream output;
 //output.open("sorted.txt");
 output.open("output.txt");
 for(int i=0;i<wordCount-1;i++){
    {

    cout << A[i] <<endl;
    cout<<data[i]

    }



}
 output.close();}

*/
