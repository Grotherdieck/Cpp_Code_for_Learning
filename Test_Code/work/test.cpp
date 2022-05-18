#define  _CRT_SECURE_NO_WARNINGS 1
// This is a C++ sample code that can be "linked" to LEKIN.
// It implements the WSPT rule for a single machine, no release times
// and no sequence-dependent setup times.  The setting is purposedly
// kept this simple in order to underline the file i/o as opposed to
// specific algorithms and data structures.

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
// we will need a data structure to store job data

struct TJob
{
    int id;           // job number
    int release;      // job release date (ignored)
    int due;          // job due date (ignored)
    int weight;       // job weight
    int proc;         // job processing time
    double wp;        // w_j / p_j
};

TJob jobArray[100];
int jobCount;

// a string buffer.
char buffer[1024];

// For the single machine setting, we don't even have to read the
// machine file.  But I'll do it to check that it actually represents
// a single machine setting.

void ReadMch()
{
    // No need to use the qualified path.  Just "_user.mch".
    ifstream Fmch("_user.mch", ios::_Nocreate);

    // Check if the file was opened.
    // If not, it is an error: probably we were called
    // standalone, NOT from LEKIN.
    // Our way of handling errors is exit(1).
    // It is a good idea to print something before exitting.

    if (!Fmch)
    {
        cout << "Machine file not found!\n";
        exit(1);
    }

    // Check the first line in the file.
    // If it is not "Ordinary:", too bad.

    Fmch.getline(buffer, 1024);
    if (strcmp(buffer, "Ordinary:"))
    {
        cout << "We do not support flexible workcenters!\n";
        exit(1);
    }

    // Now we skip several lines.  There are 2 ways to skip: getline or ignore.
    // getline allows you to check what you are skipping.

    Fmch.getline(buffer, 1024);
    // buffer = "Workcenter:        Wkc000",
    // but we don't care.

    Fmch.ignore(1024, '\n');  // skip "Setup:"
    Fmch.ignore(1024, '\n');  // skip "Machine:"

    // we don't need the avaiability time and the starting status
    // for the machine, but I'll read it just to show how it's done.
    Fmch.ignore(20);          // skip "Release:" keyword
    int avail; Fmch >> avail;
    Fmch.ignore(20);          // skip "Status:" keyword

    // counting spaces is not a good idea,
    // so just read till the first non-space
    Fmch >> ws;
    char status = Fmch.get();

    // Let's check status -- just in case...
    if (status < 'A' || status>'Z')
    {
        cout << "The file is corrupt!\n";
        exit(1);
    }

    // OK, now the rest of the file must contain nothing but
    // a bunch of white-space characters.

    Fmch >> ws;
    if (!Fmch.eof())
    {
        cout << "The file contains at least 2 workcenters!\n";
        exit(1);
    }
}

// With the job file, it is not that easy.
// We actually have to read the stream of jobs.

void ReadJob()
{
    ifstream Fjob("_user.job", ios::_Nocreate);
    if (!Fjob)
    {
        cout << "Job file not found!\n";
        exit(1);
    }

    Fjob >> buffer; // buffer = "Shop:", ignore
    Fjob >> buffer; // check if single machine
    if (strcmp(buffer, "Single"))
    {
        cout << "This is not a single machine file!\n";
        exit(1);
    }

    while (1)
    {
        Fjob >> buffer;             // buffer = "Job:"
        if (strcmp(buffer, "Job:")) // If not, must be the end of file
            break;

        Fjob >> buffer;             // buffer = "Job###", ignore
        jobArray[jobCount].id = jobCount;

        Fjob >> buffer;             // buffer = "Release:"
        Fjob >> jobArray[jobCount].release;

        Fjob >> buffer;             // buffer = "Due:"
        Fjob >> jobArray[jobCount].due;

        Fjob >> buffer;             // buffer = "Weight:"
        Fjob >> jobArray[jobCount].weight;

        Fjob >> buffer;             // buffer = "Oper:"
        Fjob >> buffer;             // buffer = "Wkc000;#;A", and we need the #
        char* ss = strchr(buffer, ';');
        if (!ss) break;
        if (sscanf(ss + 1, "%d", &jobArray[jobCount].proc) < 1) break;

        jobArray[jobCount].wp =
            double (jobArray[jobCount].proc) / (jobArray[jobCount].weight);
        jobCount++;
    }

    if (jobCount == 0)
    {
        cout << "No jobs defined!\n";
        exit(1);
    }
}

// compare function for sorting

int compare(const void* j1, const void* j2)
{
    TJob* jb1 = (TJob*)j1;
    TJob* jb2 = (TJob*)j2;
    double a = jb1->wp - jb2->wp;
    return a < 0 ? -1 : a>0 ? 1 : 0;
}

// Since this is just a single machine, we can
// implement any rule by simple sorting on the job array.
// We'll use the C standard qsort function.

void SortJobs()
{
    qsort(jobArray, jobCount, sizeof(TJob), compare);
}

// Output the schedule file

void WriteSeq()
{
    ofstream Fsch("_user.seq");
    Fsch << "Schedule: WSPT rule\n";    // schedule name
    Fsch << "Machine: Wkc000.000\n";    // name of the first (and last) machine
                                        // now enumerate the operations
    for (int i = 0; i < jobCount; i++)
        Fsch << "Oper: Job" << jobArray[i].id << "\n";
}

int main(int argc, char* argv[])
{
    // We have to have exactly 2 command line arguments:
    // objective function and time limit.

    if (argc != 3)
    {
        cout << "Illegal call!\n";
        exit(1);
    }

    // Check the objective function.  The WSPT rule is for
    // Total Weighted Flow Time (ID = 6, see LEKIN online manual).
    // We'll complain if called for a different objective.

    // don't bother to use sscanf
    if (strcmp(argv[1], "6"))
    {
        cout << "The only objective supported is \\sum w_j C_j.\n";
        exit(1);
    }

    ReadMch();
    ReadJob();
    SortJobs();
    WriteSeq();

    cout << "Success\n";
    return 0;
}
