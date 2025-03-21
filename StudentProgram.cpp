#include "StudentProgram.h"

#include "../Utilities/Style.h"
#include "../Utilities/Strings.h"
#include "../Utilities/CsvParser.h"

#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

StudentProgram::StudentProgram()
{
    //records = LoadRecords( "../Data/KansasCityMissouriParksandBoulevardsMap.csv" );
}

StudentProgram::~StudentProgram()
{
}

void StudentProgram::LoadRecords( string filename )
{
    // TODO: Add your loading functionality here!



    CsvDocument doc;
    doc = CsvParser::Parse( filename );

    ReportStatus newIssue;
    int counter = 0;
    for (size_t r = 0; r < doc.rows.size(); r++){
        for (size_t c = 0; c < doc.rows[r].size(); c++){
            if (doc.header[c] == "Reported Issue Number") {newIssue.reportedIssueNum = doc.rows[r][c]; }
            else if (doc.header[c] == "Current Status") { newIssue.currentStatus = doc.rows[r][c]; }
			else if (doc.header[c] == "Open Date Time") { newIssue.openDateTime = doc.rows[r][c]; }
			else if (doc.header[c] == "Resolved Date") { newIssue.resolvedDate = doc.rows[r][c]; }
			else if (doc.header[c] == "Issue Type") { newIssue.issueType = doc.rows[r][c]; }
            else if (doc.header[c] == "Issue Sub-Type") { newIssue.issueSubType = doc.rows[r][c]; }
			else if (doc.header[c] == "Incident Address") { newIssue.incidentAddress = doc.rows[r][c]; }
        }
        status.push_back(newIssue);
    }
}

void StudentProgram::ViewAll()
{
    DisplayHeader( "ALL RECORDS", 2 );
    cout << left << fixed << setprecision( 2 );
    cout << "  "
        << setw( 5 ) << "IDX"
        << setw( 20 ) << "INTFIELD"
        << setw( 20 ) << "STRINGFIELD"
        << endl << "  " << string( 75, '-' ) << endl;
    for ( size_t i = 0; i < status.size(); i++ )
    {
        cout << "  "
            << setw( 5 ) << i
            << setw( 20 ) << status[i].reportedIssueNum
            << setw( 20 ) << PartialString( status[i].issueType, 18 )
            << setw(20) << status[i].currentStatus
            << endl;
    }
}

void StudentProgram::Report1()
{
    DisplayHeader( "REPORT 1", 2 );
    // TODO: Add your report 1 here

    
    vector<size_t> canceledIssueIndices;
    int totalPothole = 0;


    for (size_t i = 0; i < status.size(); i++){
        if (status[i].currentStatus == "canceled"){
            canceledIssueIndices.push_back(i);
            if (status[i].issueType == "A Pothole"){
                totalPothole++;
            }
        }
    }
     cout << canceledIssueIndices.size() << " canceled issues found:" << endl;
     for (auto& index : canceledIssueIndices){
        cout << "* " << status[index].openDateTime << ", "
                       << status[index].issueType << ", "
                       << status[index].reportedIssueNum << endl;
                    
        }

    cout << "Total potholes: " << totalPothole << endl;

}

void StudentProgram::Report2()
{
    DisplayHeader( "REPORT 2", 2 );
    // TODO: Add your report 2 here

    vector<size_t> streetMaintainceIssues;
    for (size_t i = 0; i < status.size(); i++){
        if (status[i].currentStatus == "Street Maintaince"){
            streetMaintainceIssues.push_back(i);
        }
    }
     cout << streetMaintainceIssues.size() << " street maintenance issues found:" << endl;
     for (auto& index : streetMaintainceIssues){
        cout << "* " << status[index].openDateTime << ", "
                       << status[index].currentStatus << ", "
                       << status[index].incidentAddress << endl;
     }
}

void StudentProgram::Search()
{
    DisplayHeader( "SEARCH", 2 );
    cout << "  Search by what field?" << endl;
    string choice = GetChoice( { "reportedIssueNum", "currentStatus", "issueType", "incidentAddress"}, 2 ); // TODO: Add fields you want searchable

    string search_term;
    cout << "  Enter partial or full search term: ";
    cin.ignore();
    getline( cin, search_term );

    vector<ReportStatus> matches;

    for ( auto& rec : status )
    {
        if ( choice == "reportedIssueNum" && Contains( rec.reportedIssueNum, search_term, false ) )
        {
            matches.push_back( rec );
        }
        else if ( choice == "currentStatus" && Contains( ToString( rec.currentStatus ), search_term, false ) )
        {
            matches.push_back( rec );
        }
        else if ( choice == "issueType" && Contains( ToString( rec.issueType ), search_term, false ) )
        {
            matches.push_back( rec );
        }
        else if ( choice == "incidentAddress" && Contains( ToString( rec.incidentAddress ), search_term, false ) )
        {
            matches.push_back( rec );
        }
    }

    DisplayHeader( "RESULTS", 3 );
    for ( size_t i = 0; i < matches.size(); i++ )
    {
        cout << "   Match #" << i+1 << ":" << endl;
        cout << "   * Repored Issue #:  " << matches[i].reportedIssueNum << endl;
        cout << "   * Status:  " << matches[i].currentStatus << endl;
        cout << "   * Issue Type:  " << matches[i].issueType << endl;
        cout << "   * Incident Address:  " << matches[i].incidentAddress << endl;
        cout << endl;
    }
}

void StudentProgram::Sort()
{
    DisplayHeader( "SORT", 0 );
    cout << "  Sort on what field?" << endl;
    string choice = GetChoice( { "reportedIssueNum", "currentStatus", "issueType", "incidentAddress" }, 2 ); 

    cout << "  Now sorting..." << endl;
    for ( size_t i = 0; i < status.size() - 1; i++ )
    {
        for ( size_t j = 0; j < status.size() - i - 1; j++ )
        {
            bool swap_needed = false;

            if ( choice == "reportedIssueNum" && status[j].reportedIssueNum > status[j+1].reportedIssueNum )
            {
                swap_needed = true;
            }
            else if ( choice == "currentStatus" && status[j].currentStatus > status[j+1].currentStatus )
            {
                swap_needed = true;
            }

              else if ( choice == "issueType" && status[j].issueType > status[j+1].issueType )
            {
                swap_needed = true;
            }
              else if ( choice == "incidentAddress" && status[j].incidentAddress > status[j+1].incidentAddress )
            {
                swap_needed = true;
            }

            if(swap_needed){
                swap(status[j], status[j + 1]);
            }
        }
    }

    cout << "  Sorting complete." << endl;
}

void StudentProgram::Run()
{
    bool menu_running = true;
    while ( menu_running )
    {
        DisplayHeader( "PROJECT", 1 );
        string choice = GetChoice( { "QUIT", "VIEW ALL", "REPORT 1", "REPORT 2", "SEARCH", "SORT" }, 1 );
        if ( choice == "QUIT" )
        {
            menu_running = false;
        }
        else if ( choice == "VIEW ALL" )
        {
            ViewAll();
        }
        else if ( choice == "REPORT 1" )
        {
            Report1();
        }
        else if ( choice == "REPORT 2" )
        {
            Report2();
        }
        else if ( choice == "SEARCH" )
        {
            Search();
        }
        else if ( choice == "SORT" )
        {
            Sort();
        }
    }
}

