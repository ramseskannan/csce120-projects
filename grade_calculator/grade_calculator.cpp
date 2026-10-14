// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO(student)

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO(student)

    // TODO(student): declare and initialize variables
    double exam_1 = 0;
    double exam_2 = 0;
    double exam_3 = 0; //there are 3 mideterms listed in the syllabus
    int exam_count = 0;

    double hw_total = 0.0; //since the student might have multiple hw
    int hw_count = 0;

    int lw_completion = 0; //since lw is based on completion, has to be >=50
    int lw_count = 0;

    int reading_completion = 0; //reported as incomplete or complete, bnased on percent completed
    int reading_count= 0;

    int engagement_completion = 0; //since engagement is based of a certain completion
    int engagement_count = 0;

    //one final
    double final_exam_score = 0.0;
    //ik there is multiple for exams, hw, and lw since there is variables initialzed below as avereages for them


    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            exam_count += 1; //increases the exam count by 1 everytime a user inputs a new exam score
            if (exam_count == 1) { //if only one exam inputted
                exam_1 = score;
            } else if (exam_count == 2) { //if user inputs 2nd exam
                exam_2 = score;
            } else if (exam_count == 3){ //if user inputs 3rd exam
                exam_3 = score;
            }
           
            // TODO(student): process midterm exam score
        } else if (category == "final-exam") {
            final_exam_score = score; //only one final
            // TODO(student): process final exam score
        } else if (category == "hw") {
            hw_total += score; //adds the users input of hw score that is from the get_category_and_score method
            hw_count += 1; //increases hw count by 1 everytime user inputs new hw score
            // TODO(student): process hw score
        } else if (category == "lw") {
            lw_count += 1; //increasing count, regardless if scored less than 50
            if (score >= 50) {
                lw_completion +=1; //adding only if completed (meaning if it is 50 and above)
            }
            // TODO(student): process lw score
        } else if (category == "reading") {
            reading_count += 1; 
            if(score == 1){ //if completed score is 1 if not then 0 (incompletion). USING BOOLEAN TO MAKE IT EASIER
                reading_completion += 1; 
           }
            // TODO(student): process reading score
        } else if (category == "engagement") {
            engagement_count += 1;
            if (score > 0){ //anything above a 0 is considered completion
                engagement_completion += 1;
            }
           
            // TODO(student): process engagement score
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    double hw_average = 0;
    double lw_average = 0;
    double exam_average = 0;
    double reading = 0;
    double engagement = 0;
    // TODO(student): compute component averages and assign to the above variables
    // exam_average = ???; // etc.
    //received -nan error without checking if negative inputs were made, now i used if-else statements
    if (hw_total > 0){ //checking greater than 0 to ensure they arent negative for all of the inputs
        hw_average = hw_total / hw_count; 
    } else {
        hw_average = 0; //we can assume it is 0 if no scores are provided/invalid
    }
    if (hw_average > 100) { //checking the max
        hw_average = 100; //if percentage exceeded 100, make it 100 instead
    }
    //different parameter because its not the same type of averaging like homeowkr
    if(lw_count > 0) {
        lw_average = ((double)lw_completion / lw_count) * 100; //apparently it would calculate unless i make it double
    } else {
        lw_average = 0; //if none were completed
    }

    if (reading_count > 0) {
        reading = ((double)reading_completion / reading_count) * 100;
    }else {
        reading = 0; //if no readings were complete (without the added 15)

    }
    reading = reading +15; //adding the 15 bonus percentage given
    if (reading >100) { //checking the max
        reading = 100; //if percentage exceeded 100, make it 100 instead
    }

    if (engagement_count > 0) {
        engagement = ((double)engagement_completion / engagement_count) * 100;
    
    } else {
        engagement = 0; //if didnt engage in anything (without 15 bonus)
    } 
    engagement = engagement + 15;
    if (engagement > 100) { //checking the max
        engagement = 100; //if percentage exceeded 100, make it 100 instead
    }
    if (exam_count == 1){ //if only 1 exam was taken
        exam_average = float(exam_1) / 2.0; //still divide by 2 (takes highest 2 exams)
    } else if (exam_count ==2) { //if only 2 exams
        exam_average = (float(exam_1 + exam_2) / 2.0); 
    } else if (exam_count ==3){ //if all 3 exams were taken
        //dropping the lowest
        if (exam_1 <= exam_2 && exam_1 <= exam_3) {
            exam_average = (float(exam_2 + exam_3) / 2.0); //dropped 1st exam
        } else if (exam_2 <= exam_1 && exam_2 <= exam_3) {
            exam_average = (float(exam_1 + exam_3) / 2.0); //dropped 2nd exam
        }else if (exam_3 <= exam_1 && exam_3 <= exam_1) {
            exam_average = (float(exam_1 + exam_2) / 2.0); //dropped 3rd exam
        }
    } else {
        exam_average = 0.0; //the user didnt input any exam, so no exams were taken
    }
 
    //now lets calculate the final exam and exams average with the weights!

    if (final_exam_score > 0 && exam_count > 0){ //if there was a final exam and atleast one midterm taken
        exam_average = (exam_average * 36.00 + final_exam_score * 24.00) / 60.00; //calculation using weights

    } else if (exam_count > 0 && final_exam_score ==0){ //if no final was taken
        if (exam_1 == 1){ //only 1 midterm, calculatio is altered (/2 cause takes highest two)
            exam_average = exam_average * 0.3; 
        } else {
            exam_average = exam_average * 0.6; //multiple exams
        }
    } else if (final_exam_score > 0 && exam_count ==0){ //if only final exam
        exam_average = (final_exam_score * 24.0) / 60; 
    }else {
        exam_average = 0;
    }

    // TODO(student): compute weighted total of components
    //HW-20%, LW - 10% EXAMS - 36% FINAL EXAM - 24%, READING 5% +15 POINTS MAX 100 CLASENGAG - 5% +15 POINTS, 
    double weighted_total = 0;
    weighted_total = float((hw_average * .20)  +  (lw_average * .10) + 
    (exam_average *.60) + (reading * .05) + (engagement * .05));

    // TODO(student): compute final letter grade
    // 100-90 a <90 AND >= 80 B, <80 >=70 C, <70 AND >= 60, LESS THAN 60 IS F
    //had to make it decimal .5 values cause of rounding
    char final_letter_grade = 'X';
    if (weighted_total >= 89.5) {
        final_letter_grade = 'A';
    }else if (weighted_total < 89.5 && weighted_total >= 79.5){
        final_letter_grade = 'B';
    }else if (weighted_total < 79.5 && weighted_total >= 69.5){
        final_letter_grade = 'C';
    }else if (weighted_total < 69.5 && weighted_total >= 59.5){
        final_letter_grade = 'D';
    }else {
        final_letter_grade = 'F';
    };

    // Do not modify print_results since this will not help
    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them
// Even minor changes might cause you to fail test cases for the wrong reasons

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "        exam average: " << exam_average << endl;
    cout << "          hw average: " << hw_average << endl;
    cout << "          lw average: " << lw_average << endl;
    cout << "     reading average: " << reading << endl;
    cout << "  engagement average: " << engagement << endl;
    cout << "  -------------------" << endl;

    cout << "      weighted total: " << weighted_total << endl;

    cout << "  final letter grade: " << final_letter_grade << endl;
}
