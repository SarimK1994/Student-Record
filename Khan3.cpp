/**************************************************************************
 *                                                                         *
 *     Program Filename:  Khan3.cpp                                        *
 *     Author          :  Sarim Khan                                       *
 *     Date Written    :  October 10th, 2017                               *
 *     Purpose         :  To write a student record                        *
 *     Input from      :  Keyboard                                         *
 *     Output to       :  Screen                                           *
 *                                                                         *
 **************************************************************************/

#include <iostream>
using namespace std;
#include <conio.h> 
#include <string>
#include <fstream>
#include <iomanip>
struct NameRecord
{
	string LastName;
	string FirstName;
	string MI; 
};

struct GradesRecord
{
	int Program1;
	int Program2; 
	int Program3; 
	int Program4; 
	int Program5; 
	int Program6; 
	int Test1; 
	int Test2; 
	int Test3; 
	int Final; 
	double Average; 
	char LetterGrade; 
};

struct StudentRecord
{
	NameRecord Name; 
	string SSN; 
	string Major; 
	GradesRecord Grades; 
};

int CountFile(ifstream&);
void ReadRecords(ifstream&, StudentRecord*); 
void CurveGrades(StudentRecord*, int); 
void ComputeAverage(StudentRecord*, int); 
void BubbleSort(StudentRecord*, int); 
void ComputeLetterGrade(StudentRecord*, int); 
void OpenOutputFile(ofstream&);
void WriteStudentRecord(ofstream&, StudentRecord*, int);
void EndProgram(); 

int main()
{
	ifstream InFile; 
	ofstream OutFile;
    
	string x;  //variable to read in file name
	int count; //variable to obtain number of student records
    
	cout << "Please enter the name of the file: "; 
	cin >> x; 
	InFile.open(x.c_str(), ios::in);
    //open file to obtain number of student records
	count = CountFile(InFile);
    
    
	StudentRecord* Array = new StudentRecord[count];

	InFile.open(x.c_str(), ios::in);
    //reopen file to read into array
    
	ReadRecords(InFile, Array); //read records into StudentRecord array
    CurveGrades(Array, count); //curve grades prior to calculating average
	ComputeAverage(Array, count); //calculate average into array given N number of records
	BubbleSort(Array, count); //sort array based on average grade
	ComputeLetterGrade(Array, count); //compute final letter grade based on average
	OpenOutputFile(OutFile); //open outputfile louie.dat
	WriteStudentRecord(OutFile, Array, count); //write output file including last 4 of SSN, average, and letter grade
	EndProgram(); //prompt user for enter prior to closing command window
}
//end main

void EndProgram()
{
	cout << endl << "Please press enter to continue."; 
	cin.ignore(); 
	cin.get(); 
}
//end function EndProgram

void WriteStudentRecord(ofstream& OutFile, StudentRecord A[], int n)
{
	int i; 
	for (i = 0; i < n; i++)
	{
		OutFile << left << setw(15) << A[i].SSN.substr(5,4); 
		OutFile << setw(10) << setprecision(4) << A[i].Grades.Average;
		OutFile << setw(10) << A[i].Grades.LetterGrade; 
		OutFile << endl; 
	} //end for
    cout << endl << "The output file has successfully been written.";
	return;
}
// end function WriteOneStudentRecord

void OpenOutputFile(ofstream& x)
{
	x.open("louie.dat", ios::out);

	if (x.fail())
	{
		cout << "Failure to open louie.dat";
		exit(-1);
	}
	// end if
	return;
}
//end function OpenOutputFile

void ComputeLetterGrade(StudentRecord A[], int n)
{
	double storeAvg; 
	int i;
	for (i = 0; i < n; i++)
	{
		storeAvg = A[i].Grades.Average; 

		if (storeAvg > 89)
		{
			A[i].Grades.LetterGrade = 'A';
		} //end if
		else if (storeAvg > 79)
		{
			A[i].Grades.LetterGrade = 'B';
		} //end else if
		else if (storeAvg > 69)
		{
			A[i].Grades.LetterGrade = 'C';
		} //end else if
		else if (storeAvg > 59)
		{
			A[i].Grades.LetterGrade = 'D';
		} //end else if
		else
		{
			A[i].Grades.LetterGrade = 'F';
		} //end else
	} //end for
	return; 
}
//end function ComputeGrades

void BubbleSort(StudentRecord A[], int n)
{
	int i, j; 
	StudentRecord temp; 
	
	for (i = n - 1; i >= 0; i--)
		for (j = 1; j <= i; j++)
			if (A[j - 1].Grades.Average < A[j].Grades.Average)
			{
				temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
			}
			//end if
		//end for
	//end for
	return; 
}
//end BubbleSort

void ComputeAverage(StudentRecord A[], int n)
{
	int i;
    double programs, tests, exam, programaverage, testaverage, examaverage, compositeaverage;
    
	for (i = 0; i < n; i++)
	{
		programs = A[i].Grades.Program1 + A[i].Grades.Program2 + A[i].Grades.Program3 + A[i].Grades.Program4
			+ A[i].Grades.Program5 + A[i].Grades.Program6; //compute total points for programs

		tests = A[i].Grades.Test1 + + A[i].Grades.Test2 + A[i].Grades.Test3; //compute total points for tests
 
		exam = A[i].Grades.Final; //compute final exam grade

		programaverage = (programs / 120) * 100; //obtain program average
		testaverage = (tests / 300) * 100;  //obtain test average
		examaverage = (exam / 100) * 100; //obtain exam average
		compositeaverage = (programaverage * .30) + (testaverage * .40) + (examaverage * .30); //obtain total average

		A[i].Grades.Average = compositeaverage; //declare StudentRecord value for overall average
	} //end for
    return;
}
//end function ComputeAverage

void ReadRecords(ifstream& InFile, StudentRecord A[])
{
	int i = 0; 
	string NextRecord; 

	getline(InFile, NextRecord); 
	
	while (!InFile.eof())
	{
		A[i].Name.LastName = NextRecord.substr(0, 15); 
		A[i].Name.FirstName = NextRecord.substr(15, 10); 
		A[i].Name.MI = NextRecord.substr(25, 1); 
		A[i].SSN = NextRecord.substr(26, 9); 
		A[i].Major = NextRecord.substr(35, 20);
		A[i].Grades.Program1 = atoi(NextRecord.substr(55, 2).c_str());
		A[i].Grades.Program2 = atoi(NextRecord.substr(57, 2).c_str());
		A[i].Grades.Program3 = atoi(NextRecord.substr(59, 2).c_str());
		A[i].Grades.Program4 = atoi(NextRecord.substr(61, 2).c_str());
		A[i].Grades.Program5 = atoi(NextRecord.substr(63, 2).c_str());
		A[i].Grades.Program6 = atoi(NextRecord.substr(65, 2).c_str());
		A[i].Grades.Test1 = atoi(NextRecord.substr(67, 3).c_str());
		A[i].Grades.Test2 = atoi(NextRecord.substr(70, 3).c_str());
		A[i].Grades.Test3 = atoi(NextRecord.substr(73, 3).c_str());
		A[i].Grades.Final = atoi(NextRecord.substr(76, 3).c_str());
		getline(InFile, NextRecord);
		i++;
        //read each student record into array
	}
	return; 
}
//end readrecords 

void CurveGrades(StudentRecord A[], int n)
{
	int i;
	int highest1 = 0; 
	int highest2 = 0; 
	int highest3 = 0; 
	int curve1, curve2, curve3; 

	for (i = 0; i < n; i++)
	{
		if (A[i].Grades.Test1 > highest1)
		{
			highest1 = A[i].Grades.Test1; //obtain highest test score for test 1
		} //end if
		if (A[i].Grades.Test2 > highest2)
		{
			highest2 = A[i].Grades.Test2; //obtain highest test score for test 2
		} //end if
		if (A[i].Grades.Test3 > highest3)
		{
			highest3 = A[i].Grades.Test3; //obtain highest test score for test 3
		} //end if
	} //end for
 
	if (highest1 < 100)
	{
		curve1 = 100 - highest1;

		for (i = 0; i < n; i++)
		{
			A[i].Grades.Test1 += curve1; //if highest test score < 100, add curve
		} //end for
	} //end if

	if (highest2 < 100)
	{
		curve2 = 100 - highest2;

		for (i = 0; i < n; i++)
		{
			A[i].Grades.Test2 += curve2; //if highest test score < 100, add curve
		} //end for
	} //end if

	if (highest3 < 100)
	{
		curve3 = 100 - highest3;

		for (i = 0; i < n; i++)
		{
			A[i].Grades.Test3 += curve3; //if highest test score < 100, add curve
		} //end for
	} //end if
	return; 
}
//end curve 

int CountFile(ifstream& InFile)
{
	string NextRecord;
	int count = 0;

	if (InFile.fail())
	{
		cout << "Failure to open input file.";
		exit(-1);
	}
	// end if
	getline(InFile, NextRecord);

	while (!InFile.eof())
	{
		count++;
		getline(InFile, NextRecord);
	} //end while
    
	InFile.close(); 
	return count;
}
//end count
