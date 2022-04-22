#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Setting up default value of my winner which is the start of the array;
    string winner = candidates[0].name;
    // Looping till the last candidate.
    for (int i = 0; i < candidate_count; i++)
    {
        // A nested loop.
        // The point is that i stands for the candidate I am at's votes, and J stands for the rest of the candidates.
        // It checks if there are multiple candidates with same votes, if there are, they both are printed out.
        for (int j = 0; j < candidate_count; j++)
        {
            // To avoid checking for itself.
            if (j == i)
            {
                continue;
            }
            else
            {
                // Checking for multiple winners.
                if (candidates[i].votes == candidates[j].votes)
                {
                    printf("%s\n", candidates[i].name);
                    printf("%s\n", candidates[j].name);
                }
            }
        }
    }
    // Candidate_count-1 because the point of the loop is for each iteration it checks the current iteration and the one after it.
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (candidates[i].votes > candidates[i + 1].votes)
        {
            winner = candidates[i].name;
        }
        else
        {
            winner = candidates[i + 1].name;
        }
    }
    // Printing out the winner;
    printf("%s\n", winner);
}