import csv
import sys


# def consec_run_dna(sequence, sample):
    

def main():
    # check for correct number of command line arguments 
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py databases/.csv sequences/.txt")
    # Open csv file in read mode    
    with open(sys.argv[1], "r") as csv_file:
        reader_csv = csv.DictReader(csv_file)
        fields = reader_csv.fieldnames[1:]
        database = list(reader_csv)
       
    # Open txt file in read mode
    with open(sys.argv[2], "r") as dna_file:
        dna_reader = dna_file.read()
        # for row in dna_reader:
        #     dna_list = row
        
    # Create list to find the max count for each dna sequence
    dna_maxcounts = []
    # Iterate through the dna sequences comparing to database 
    for i in range(len(database)):
        # Set variable to count matches between the database and the STRs
        match = 0
        # print(database)
        for j in dna_reader:
            # Set seq variable to 1 to account for 1st sequence
            seq = 1
            # Trying to check if sequence matches name but at this point I'm lost and out of time
            while fields[i] * seq in dna_reader:
                seq += 1
            
            if (seq - 1) > match:
                match = seq - 1
        # Adding matches to the list        
        dna_maxcounts.append(match)
        print(match)
  
        
if __name__ == "__main__":
    main()    