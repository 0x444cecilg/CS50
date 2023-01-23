#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // loop through candidates
    {
        if (strcmp(candidates[i].name, name) == 0) // compare user input to array name
        {
            preferences[voter][rank] = i; // assign ranking to candidate for each voter

            return true;
        }

    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
// I had to get help from a programmer friend to figure out the syntax 'candidates[preferences[i][j].eliminated'
{
    // TODO
    for (int i = 0; i < voter_count; i++) // loop through voter count
    {
        int j = 0;
        while (candidates[preferences[i][j]].eliminated == true) // if candidate eliminated increase rank
        {
            j++;
        }
        if (candidates[preferences[i][j]].eliminated == false) // if not eliminated increase vote
        {
            candidates[preferences[i][j]].votes++;
        }
    }

}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO


    for (int i = 0; i < candidate_count; i++)
    {
        int majority = voter_count / 2 + 0.5;
        // create variable for majority vote, for some reason adding 0.5 as opposed to 1 or 2 gave the majority??
        if (candidates[i].votes > majority) // candidate with more than 50% of vote wins
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false; // if none have more than 50% return false
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min_vote = candidates[0].votes; // make variable set to 1st candidates vote
    for (int i = 1; i < candidate_count; i++) // loop through candidates
    {

        if (candidates[i].eliminated == false && candidates[i].votes < min_vote)
        // check for those still in race and compare their vote to the minimum
        {
            min_vote = candidates[i].votes; // if condition met set candidates vote to the minimum vote
        }

    }
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min_vote)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // loop through candidates
    {
        if (candidates[i].eliminated == false && candidates[i].votes > min_vote) // if candidates are not tied return false else return true
        {
            return false;
        }
    }
    return true;
}
// Eliminate the candidate (or candidates) in last place
void eliminate(int min_vote)
{
    // TODO

    for (int i = 0; i < candidate_count; i++) // loop through candidates
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min_vote) // eliminate candidates with lowest vote
        {
            candidates[i].eliminated = true;
        }
    }

}
