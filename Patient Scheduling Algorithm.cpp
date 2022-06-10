#include <bits/stdc++.h>
#include <queue>
using namespace std;

struct schedule
{
    int entry_time;
    int timeToCompletion;
};
struct myComparator
{
    bool operator()(schedule a, schedule b)
    {
        // sorting in ascending order of entry time
        return a.entry_time > b.entry_time;
    }
};

int main()
{

    // Input below
    // We are given the entry time and the time to completion of a patient
    // Assuming entry time: 600 -> 6 pm
    // Assuming Time to completion: 100 -> 1 hour (for simplicity)

    // Priority Queue - Min heap - on Objects/ Struct
    priority_queue<schedule, vector<schedule>, myComparator> pq;

    // {entry time, time to completition}                         Exit time
    pq.push({600, 100});    // 600 -> 6 pm, 100 -> 1 hour          700
    pq.push({650, 05});     //                                     655
    pq.push({700, 500});    //                                     1200
    pq.push({750, 100});    //                                     850
    pq.push({800, 10});     //                                     810
    pq.push({850, 60});     //                                     910
    pq.push({900, 30});     //                                     930
    pq.push({910, 30});     //                                     940
    pq.push({920, 30});     //                                     950
    pq.push({1000, 100});   //                                     1100

    cout << "Total number of patients in the input data = " << pq.size() << endl;

    priority_queue<schedule, vector<schedule>, myComparator> pq_of_patients;
    int current_bed_count = 0;
    int max_bed_count = 0;

    while (!pq.empty())
    {
        // For the second priorit queue named pq_of_patients
        // We are storing the exit_time and bed_count of patients. 
        // using pair of {endtime, bed_number} in pq_of_patients.
        schedule pq_element = pq.top();
        int end_time = pq_element.entry_time + pq_element.timeToCompletion;
        int sizePQ1 = pq_of_patients.size();
        if (sizePQ1 == 0)
        {
            cout << "First Insert, a new bed will be assigned" << endl;
            current_bed_count++;
            pq_of_patients.push({end_time, current_bed_count});
        }

        else if (pq_of_patients.top().entry_time >= pq_element.entry_time)
        {
            cout << "\n\nCase: Exit time (of patients in hospital) >= Entry time of the current patient (before assigning a bed)";
            cout << "\nPatient having least Exit_Time = " << pq_of_patients.top().entry_time << ", Current patient's entry time = " << pq_element.entry_time << endl;
            current_bed_count++;
            pq_of_patients.push({end_time, current_bed_count});
        }
        else if (pq_of_patients.top().entry_time < pq_element.entry_time)
        {
            while (pq_of_patients.top().entry_time < pq_element.entry_time)
            {
                // Reduce the number of beds till all the patients whose exit time is less than the entry time of a new/current patient
                // Basically, all the patients which are present in hospital has to move out on their respective exit times
                // We are simply reducing the number of beds, for every patient whose exit time is less than the current patient's extry time.
                cout << "\n\nCase: Exit time (of patients in hospital) < Entry time of the current patient (before assigning a bed)";
                cout << "\nPatient having least Exit_Time = " << pq_of_patients.top().entry_time << ", Current patient's entry time = " << pq_element.entry_time << endl;
                pq_of_patients.pop();
                current_bed_count--;
            }
            if (pq_of_patients.top().entry_time >= pq_element.entry_time)
            {
                // Since we have to assign this current patient a new bed.
                current_bed_count++;
            }
            pq_of_patients.push({end_time, current_bed_count});
        }

        // Checking and updating the maximum number of beds required at any given moment
        if(current_bed_count > max_bed_count) {
            max_bed_count = current_bed_count;
        }
        cout << "Current bed count = " << current_bed_count << ", Max bed count = " << max_bed_count << endl;
        pq.pop();
    }

    cout << "\n\nNumber of patients remaining in hospital = " << pq_of_patients.size() << endl;

    cout << "Max beds required = " << max_bed_count << endl;

    cout << "\n\nRemaining elements(patients) in the hospital (Displaying their exit time):\n";

    while (!pq_of_patients.empty())
    {
        cout << "Patient's exit time = " << pq_of_patients.top().entry_time << endl;
        pq_of_patients.pop();
    }

    return 0;
}
