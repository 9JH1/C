#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

char *dateCur;

// Function to convert date from iCalendar format to a readable format
void format_date(const char *datetime, char *formatted_date) {
    snprintf(formatted_date, 11, "%c%c/%c%c/%c%c%c%c",
             datetime[6], datetime[7],
             datetime[4], datetime[5],
             datetime[0], datetime[1],
             datetime[2], datetime[3]);
}

// Function to format time from iCalendar format to HH:MM
void format_time(const char *time_str, char *formatted_time) {
    snprintf(formatted_time, 6, "%c%c:%c%c",
             time_str[0], time_str[1],
             time_str[2], time_str[3]);
}

// Function to print the event details
void print_event(const char *date, const char *summary, const char *start_time, const char *end_time, const char *location) {
    if(strcmp(dateCur,date)==0){ 

        dateCur = date;
        printf("%s\n", date);
    }
    printf("    %s:%s - %s at %s\n", summary, start_time, end_time, location);
}

// Function to process the iCalendar file and print events
void process_ics_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    char summary[64] = "", location[64] = "", start[16] = "", end[16] = "";
    char date[11], start_time[6], end_time[6];
    int inside_event = 0;

    while (fgets(line, sizeof(line), file)) {
        // Check for start of an event
        if (strstr(line, "BEGIN:VEVENT") != NULL) {
            inside_event = 1;
        }
        // Check for end of an event
        else if (strstr(line, "END:VEVENT") != NULL) {
            if (inside_event) {
                // Format the date and time for output
                if (start[0] && end[0]) {  // Check if start and end times are available
                    format_date(start, date);
                    format_time(start + 9, start_time);
                    format_time(end + 9, end_time);
                    print_event(date, summary, start_time, end_time, location);
                }
                inside_event = 0;
                // Clear the variables for the next event
                memset(summary, 0, sizeof(summary));
                memset(location, 0, sizeof(location));
                memset(start, 0, sizeof(start));
                memset(end, 0, sizeof(end));
            }
        }
        // Parse event details
        else if (inside_event) {
            if (strstr(line, "SUMMARY:") == line) {
                sscanf(line, "SUMMARY:%[^\n]", summary);
            } else if (strstr(line, "LOCATION:") == line) {
                sscanf(line, "LOCATION:%[^\n]", location);
            } else if (strstr(line, "DTSTART;TZID=Pacific/Auckland:") == line) {
                // Extract date and time assuming format is "DTSTART;TZID=Pacific/Auckland:20240202T100000"
                sscanf(line, "DTSTART;TZID=Pacific/Auckland:%8sT%s", start, start + 9);
            } else if (strstr(line, "DTEND;TZID=Pacific/Auckland:") == line) {
                // Extract date and time assuming format is "DTEND;TZID=Pacific/Auckland:20240202T105500"
                sscanf(line, "DTEND;TZID=Pacific/Auckland:%8sT%s", end, end + 9);
            }
        }
    }

    fclose(file);
}

int main() {
    process_ics_file("data.ics");
    return 0;
}
