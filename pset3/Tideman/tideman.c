#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

int get_index(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate_index = get_index(name);
        if (candidate_index != -1)
        {
            ranks[rank] = candidate_index;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ ranks[i] ][ ranks[j] ]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair p;
                p.winner = i;
                p.loser = j;
                pairs[pair_count++] = p;
            }
        }
    }
    return;
}
// Sort algorithme
int compare(const void *elm1, const void *elm2)
{
    pair f = *((pair *) elm1);
    pair s = *((pair *) elm2);
    int first_margin = preferences[f.winner][f.loser] - preferences[f.loser][f.winner];
    int second_margin = preferences[s.winner][s.loser] - preferences[s.loser][s.winner];
    return second_margin - first_margin;
}

// Sort pairs in decreasing order by strength o f victory
void sort_pairs(void)
{
    // TODO
    qsort(pairs, pair_count, sizeof(pair), compare);
    return;
}

bool has_cycle_helper(int index, bool visited[])
{
    if (visited[index])
    {
        return true;
    }
    visited[index] = true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[index][i] && has_cycle_helper(i, visited))
        {
            return true;
        }
    }
    return false;
}

bool has_cycle(int starting_index)
{
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }
    return has_cycle_helper(starting_index, visited);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        // Check for cycle in the directed grath starting with the ith candidate
        if (has_cycle(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

bool is_root(int index)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][index])
        {
            return false;
        }
    }
    return true;
}

int get_root()
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_root(i))
        {
            return i;
        }
    }
    return -1;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int index = get_root();
    if (index != -1)
    {
        printf("%s\n", candidates[index]);
    }
}

