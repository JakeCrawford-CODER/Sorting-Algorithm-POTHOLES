#ifndef _STUDENT_PROGRAM
#define _STUDENT_PROGRAM

#include <string>
#include <vector>
using namespace std;

// TODO: Put your struct here!
struct ReportStatus
{
    string reportedIssueNum;
     string currentStatus;
     string openDateTime;
     string resolvedDate;
     string issueType;
     string issueSubType;
     string incidentAddress;

};

class StudentProgram
{
    public:
    StudentProgram();
    ~StudentProgram();

    void LoadRecords( string filename );

    void ViewAll();
    void Report1();
    void Report2();
    void Search();
    void Sort();
    void Run();

    private:
    vector<ReportStatus> status;
};

#endif
