#!/bin/bash

# Step 1: Compile the Code
echo "Compiling the code..."
cd /home/anik/CSE478.1-Graph_Theory/EBBkC/src/build
make clean  # Clean previous builds
make        # Compile the code

if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi 

echo "Compilation successful."

# Step 2: Pre-processing (Optional)
# echo "Running pre-processing..."
# ./BBkC p /home/anik/EBBkC/dataset/facebook/facebook.edges
# ./BBkC p /home/anik/EBBkC/dataset/nasasrb/nasasrb.edges


# Step 3: Run Serial Listing Procedure for Facebook
echo "Running serial listing for Facebook dataset..."
./BBkC e ../../dataset/facebook 20 3
echo "Serial listing for Facebook dataset completed."


# Step 4: Run Serial Listing Procedure for Nasasrb
echo "Running serial listing for Nasasrb dataset..."
./BBkC e ../../dataset/nasasrb 12 2
echo "Serial listing for Nasasrb dataset completed."

echo "All tasks completed."

# Step 5: Convert Edgelist to Binary
# cd /home/anik/CSE478.1-Graph_Theory/EBBkC/Cohesive_subgraph_book/datasets
# ./edgelist2binary /home/anik/CSE478.1-Graph_Theory/EBBkC/dataset/facebook facebook.clean
# ./edgelist2binary /home/anik/CSE478.1-Graph_Theory/EBBkC/dataset/nasasrb nasasrb.clean


# chmod +x run_clique.sh
# ./run_clique.sh