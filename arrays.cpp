#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

// For windows development
typedef unsigned int uint;

using namespace std;

/*
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

    void push(int x) Pushes element x to the back of the queue.
    int pop() Removes the element from the front of the queue and returns it.
    int peek() Returns the element at the front of the queue.
    boolean empty() Returns true if the queue is empty, false otherwise.

Notes:

    You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
    Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
*/
class MyQueue {
public:
    /*
    Idea - one stack holds all the elements when popping and one stack holds all the elements when pushing and they transfer the elements back and forth.
    */
    MyQueue() {
        justPushed = true;
        size = 0;
    }
    
    void push(int x) {
        // Do transfer if needed
        transferElements(true);

        // Push element onto the stack
        pushStack.push_back(x);
        size++;
    }
    
    int pop() {
        // Do transfer
        transferElements(false);

        // Pop element from the stack
        if(size >= 1){
            int val = popStack[size - 1];
            popStack.pop_back();
            size--;
            return val;
        }

        // Should be some kind of error code but here we are
        return -1;
    }
    
    int peek() {
        // Do transfer
        transferElements(false);

        if(size >= 1){
            return popStack[size - 1];
        }

        // Should be some kind of error code but here we are
        return -1;
    }
    
    bool empty() {
        return size == 0;
    }

private:
    //----- MEMBER FIELDS -----
    // Flag for if the last operation does was a push
    bool justPushed;
    // Stack holding elements when doing pushes
    vector<int> pushStack;
    // Stack holding elements when doing pops and peeks
    vector<int> popStack;
    // Size
    int size;

    //----- MEMBER FUNCTIONS -----
    void transferElements(bool toPush){
        if(toPush && !justPushed){
            // Transfer from pop to push
            for(int i = 0; i < size; i++){
                pushStack.push_back(popStack[popStack.size() - 1]);
                popStack.pop_back();
            }
            justPushed = true;
        } else if(!toPush && justPushed){
            // Transfer from push to pop
            for(int i = 0; i < size; i++){
                popStack.push_back(pushStack[pushStack.size() - 1]);
                pushStack.pop_back();
            }
            justPushed = false;
        }
        // Other two conditions do not require transfer
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

// Leet Code Arrays Quest Problems
class Solution {
public:
    /*
    Given an integer array nums of length n, you want to create an array ans of length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed).

    Specifically, ans is the concatenation of two nums arrays.

    Return the array ans.
    */
    vector<int> getConcatenation(vector<int>& nums) {
        // Copy first n elements
        vector<int> result(nums);

        // Copy remaining if needed
        if(nums.size() > 0){
            // First elements

            // Remaining
            for(uint i = 0; i < nums.size(); i++){
                result.push_back(nums[i]);
            }
        }

        return result;
    }

    void test_getConcatenation(){
        // Tests
        vector<int> input = {1,2,1};
        vector<int> exp = {1,2,1,1,2,1};
        vector<int> res = getConcatenation(input);
        
        // Check elements of vector
        bool validation = exp.size() == res.size();
        int indexDiff;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    Given the array nums consisting of 2n elements in the form [x1,x2,...,xn,y1,y2,...,yn].

    Return the array in the form [x1,y1,x2,y2,...,xn,yn].
    */
    vector<int> shuffle(vector<int>& nums, int n) {
        //----- INITIALIZATION -----
        // The result
        vector<int> result(2*n);
        
        //----- ALGORITHM -----
        for(int i = 0; i < n; i++){
            // Copy x_i
            result[2*i] = nums[i];
            // Copy y_i
            result[2*i + 1] = nums[n + i];
        }

        return result;
    }

    void test_shuffle(){
        // Test 1
        vector<int> input = {2,5,1,3,4,7};
        vector<int> exp = {2,3,5,4,1,7};
        vector<int> res = shuffle(input, 3);
        
        // Check elements of vector
        bool validation = exp.size() == res.size();
        int indexDiff;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 2
        input = {1,2,3,4,4,3,2,1};
        exp = {1,4,2,3,3,2,4,1};
        res = shuffle(input, 4);
        
        // Check elements of vector
        validation = exp.size() == res.size();
        indexDiff = -1;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 2: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 3
        input = {1,1,2,2};
        exp = {1,2,1,2};
        res = shuffle(input, 2);
        
        // Check elements of vector
        validation = exp.size() == res.size();
        indexDiff = -1;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 3: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    Given a binary array nums, return the maximum number of consecutive 1's in the array.

    Note: Probably a stupid bit shift way to do this that I am not smart enough to figure out...
    */
    int findMaxConsecutiveOnes(vector<int>& nums) {
        //----- INITALIZATIONS -----
        // Current max length
        int max = 0;
        // Left index to track
        int left = -1;
        // Right index to track
        int right = -1;
        // Current index
        uint i = 0;

        //----- ALGORITHM -----
        while(i < nums.size()){
            // Find start of one's chain
            while(i < nums.size() && nums[i] == 0){
                i++;
            }
            left = i;

            // Find next zero or end
            while(i < nums.size() && nums[i] == 1){
                i++;
            }
            right = i;

            // Update max if appropriate
            if(right - left > max){
                max = right - left;
            }
        }

        return max;
    }

    void test_findMaxConsecutiveOnes(){
        // Test 1:
        vector<int> input = {1,1,0,1,1,1};
        int exp = 3; 
        int res = findMaxConsecutiveOnes(input);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 2:
        input = {1,0,1,1,0,1};
        exp = 2; 
        res = findMaxConsecutiveOnes(input);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 3:
        input = {1,1,0,1};
        exp = 2; 
        res = findMaxConsecutiveOnes(input);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and loss of another number.

    You are given an integer array nums representing the data status of this set after the error.

    Find the number that occurs twice and the number that is missing and return them in the form of an array.

    Does not have to be sorted.
    */
   vector<int> findErrorNums(vector<int>& nums) {
        //----- INITIALIZATION -----
        // Final result
        vector<int> result = {-1, -1};
        // Count of all values
        vector<int> countVals(nums.size());
        for(uint i = 0; i < countVals.size(); i++){
            countVals[i] = 0;
        }

        //----- ALGORITHM -----
        // Count the number of each number in the array
        for(uint i = 0; i < nums.size(); i++){
            countVals[nums[i] - 1]++;
        }

        // Find the one that's 2 and the one that's zero
        for(uint i = 0; i < countVals.size(); i++){
            if(countVals[i] == 0){
                result[1] = i + 1;
            } else if(countVals[i] == 2){
                result[0] = i + 1;
            }
        }

        return result;
    }

    void test_findErrorNums(){
        // Test 1:
        vector<int> input = {1,2,2,4};
        vector<int> exp = {2,3}; 
        vector<int> res = findErrorNums(input);
        cout << "Test 1: ";
        if(exp[0] == res[0] && exp[1] == res[1]){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: [" << exp[0] << "," << exp[1] << "] Result: [" << res[0] << "," << res[1] << "]" << endl;
        }

        // Test 2:
        input = {1,1};
        exp = {1,2}; 
        res = findErrorNums(input);
        cout << "Test 2: ";
        if(exp[0] == res[0] && exp[1] == res[1]){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: [" << exp[0] << "," << exp[1] << "] Result: [" << res[0] << "," << res[1] << "]" << endl;
        }

    }

    /*
    Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it. That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].

    Return the answer in an array.

    0 <= nums[i] <= 100
    */
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        // REFACTOR: 100 is small in the grand scheme of things, but could make cumulative sum algorithm slightly more efficient by cutting off at max value in nmums

        //----- INITIALIZATION -----
        // Final result
        vector<int> result(nums.size());
        // Cumulative sum of all numbers of this size
        vector<int> cumSum(101);
        for(uint i = 0; i < cumSum.size(); i++){
            cumSum[i] = 0;
        }

        //----- ALGORITHM -----
        // Count the number of each number in the array
        for(uint i = 0; i < nums.size(); i++){
            cumSum[nums[i]]++;
        }
        // Create cumulative sum
        for(uint i = 1; i < cumSum.size(); i++){
            cumSum[i] = cumSum[i] + cumSum[i - 1];
        }

        // Use cumulative sum to calculate the result
        for(uint i = 0; i < result.size(); i++){
            if(nums[i] == 0){
                result[i] = 0;
            } else {
                result[i] = cumSum[nums[i] - 1];
            }
        }

        return result;
    }

    void test_smallerNumbersThanCurrent(){
        // Test 1
        vector<int> input = {8,1,2,2,3};
        vector<int> exp = {4,0,1,1,3};
        vector<int> res = smallerNumbersThanCurrent(input);
        
        // Check elements of vector
        bool validation = exp.size() == res.size();
        int indexDiff;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 2
        input = {6,5,4,8};
        exp = {2,1,0,3};
        res = smallerNumbersThanCurrent(input);
        
        // Check elements of vector
        validation = exp.size() == res.size();
        indexDiff = -1;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 2: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 3
        input = {7,7,7,7};
        exp = {0,0,0,0};
        res = smallerNumbersThanCurrent(input);
        
        // Check elements of vector
        validation = exp.size() == res.size();
        indexDiff = -1;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 3: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        
        // Test 3
        input = {5,0,10,0,10,6};
        exp = {2,0,4,0,4,3};
        res = smallerNumbersThanCurrent(input);
        
        // Check elements of vector
        validation = exp.size() == res.size();
        indexDiff = -1;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 4: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
    */
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        //----- INITIALIZATION -----
        // Final result
        vector<int> result = {};
        // Cumulative of number in array
        vector<int> counts(nums.size());
        for(uint i = 0; i < counts.size(); i++){
            counts[i] = 0;
        }

        //----- ALGORITHM -----
        // Count the number of each number in the array
        for(uint i = 0; i < nums.size(); i++){
            counts[nums[i] - 1]++;
        }

        for(uint i = 0; i < counts.size(); i++){
            if(counts[i] == 0){
                result.push_back(i + 1);
            }
        }

        return result;
    }

    void test_findDisappearedNumbers(){
        // Test 1
        vector<int> input = {4,3,2,7,8,3,1};
        vector<int> exp = {5,6};
        vector<int> res = findDisappearedNumbers(input);
        
        // Check elements of vector
        bool validation = exp.size() == res.size();
        int indexDiff;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 2
        input = {1,1};
        exp = {2};
        res = findDisappearedNumbers(input);
        
        // Check elements of vector
        validation = exp.size() == res.size();
        indexDiff = -1;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 2: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    You are given an integer array target and an integer n.

    You have an empty stack with the two following operations:

        "Push": pushes an integer to the top of the stack.
        "Pop": removes the integer on the top of the stack.

    You also have a stream of the integers in the range [1, n].

    Use the two stack operations to make the numbers in the stack (from the bottom to the top) equal to target. You should follow the following rules:

        If the stream of the integers is not empty, pick the next integer from the stream and push it to the top of the stack.
        If the stack is not empty, pop the integer at the top of the stack.
        If, at any moment, the elements in the stack (from the bottom to the top) are equal to target, do not read new integers from the stream and do not do more operations on the stack.

    Return the stack operations needed to build target following the mentioned rules. If there are multiple valid answers, return any of them.

    NGL, this question is confusing. I think the idea is that we push numbers onto the stack so that we build toward the target and record the operations. The stream goes from 1 to n? I feel like it's supposed to be modeling something, but honestly, it doesn't super make sense.
    */
   vector<string> buildArray(vector<int>& target, int n) {
        // REFACTOR: we only care about the result, so could easily just build the result based on the contents of target

        //----- INITIALIZATION -----
        // Result - operations used to build the target
        vector<string> result;
        // Stack to store the stack being used
        vector<int> stack(target.size());
        // Index to track where we are in the target
        uint index = 0;
        // Value from the stream
        int val = 1;
        // Flag for completion
        bool done = false;

        //----- ALGORITHM -----
        while(!done){
            // Push number onto the stack
            stack[index] = val;
            result.push_back("Push");

            // Check if we want the number
            if(index == target.size() - 1 && stack[index] == target[index]){
                done = true;
            } else if(stack[index] != target[index]) {
                result.push_back("Pop");
            } else {
                index++;
            }

            val++;
        }

        return result;
    }

    void test_buildArray(){
        vector<int> target = {1,3};
        int n = 3;
        vector<string> exp = {"Push", "Push", "Pop", "Push"};
        vector<string> res = buildArray(target, n);

        // Check elements of vector
        bool validation = exp.size() == res.size();
        int indexDiff;
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

    Evaluate the expression. Return an integer that represents the value of the expression.

    Note that:

        The valid operators are '+', '-', '*', and '/'.
        Each operand may be an integer or another expression.
        The division between two integers always truncates toward zero.
        There will not be any division by zero.
        The input represents a valid arithmetic expression in a reverse polish notation.
        The answer and all the intermediate calculations can be represented in a 32-bit integer.
    
    Ok, this problem is solved by a stack.
    */
    int evalRPN(vector<string>& tokens) {
        //----- INITIALIZATION -----
        // Stack to track operations
        vector<int> stack(tokens.size());
        // Current index of the top of the stack
        int indexTop = -1;

        //----- ALGORITHM -----
        for(uint i = 0; i < tokens.size(); i++){
            if(tokens[i] == "+") {
                stack[indexTop - 1] = stack[indexTop - 1] + stack[indexTop];
                indexTop -= 1;
            } else if(tokens[i] == "-") {
                stack[indexTop - 1] = stack[indexTop - 1] - stack[indexTop];
                indexTop -= 1;
            } else if(tokens[i] == "*") {
                stack[indexTop - 1] = stack[indexTop - 1] * stack[indexTop];
                indexTop -= 1;
            } else if(tokens[i] == "/") {
                stack[indexTop - 1] = stack[indexTop - 1] / stack[indexTop];
                indexTop -= 1;
            } else {
                indexTop++;
                stack[indexTop] = stoi(tokens[i]);
            }
        }

        return stack[0];
    }

    void test_evalRPN(){
        // Test 1
        vector<string> input = {"2","1","+","3","*"};
        int exp = 9;
        int res = evalRPN(input);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 2
        input = {"4","13","5","/","+"};
        exp = 6;
        res = evalRPN(input);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 3
        input = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
        exp = 22;
        res = evalRPN(input);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    On a single-threaded CPU, we execute a program containing n functions. Each function has a unique ID between 0 and n-1.

    Function calls are stored in a call stack: when a function call starts, its ID is pushed onto the stack, and when a function call ends, its ID is popped off the stack. The function whose ID is at the top of the stack is the current function being executed. Each time a function starts or ends, we write a log with the ID, whether it started or ended, and the timestamp.

    You are given a list logs, where logs[i] represents the ith log message formatted as a string "{function_id}:{"start" | "end"}:{timestamp}". For example, "0:start:3" means a function call with function ID 0 started at the beginning of timestamp 3, and "1:end:2" means a function call with function ID 1 ended at the end of timestamp 2. Note that a function can be called multiple times, possibly recursively.

    A function's exclusive time is the sum of execution times for all function calls in the program. For example, if a function is called twice, one call executing for 2 time units and another call executing for 1 time unit, the exclusive time is 2 + 1 = 3.

    Return the exclusive time of each function in an array, where the value at the ith index represents the exclusive time for the function with ID i.
    
    The book keeping on this problem is ass, but whatever... end means end of the time unit, start means start of the time unit, so do with that what we will...
    */
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        //----- EDGE CASES -----
        if(n == 1){
            // Pull out the final number and add 1
            int pos = logs[logs.size() - 1].find(':');
            string tmp = logs[logs.size() - 1].substr(pos + 1);
            pos = tmp.find(':');
            return {stoi(tmp.substr(pos + 1)) + 1};
        }

        //----- INITIALIZATION -----
        // The result
        vector<int> result(n);
        for(int i = 0; i < n; i++){
            result[i] = 0;
        }
        // Function number
        int function;
        // Start or end, true for start
        bool startEnd;
        // Time unit of operation
        int timeUnit;
        // Position for parsing
        int pos;
        // Temp string for parsing
        string tmp;
        // Stack for pairs of start and time unit
        vector<pair<int, bool>> stack(logs.size() / 2);
        // Index of the end
        int indexTop = 0;
        // Previous time unit
        int prevTimeUnit = 0;
        // Start or End of time unit
        bool prevTimeUnitStartEnd = true;

        //----- ALGORITHM -----
        // Parse first log
        // Extract function
        pos = logs[0].find(':');
        function = stoi(logs[0].substr(0, pos));
        // Extract if start or end
        tmp = logs[0].substr(pos + 1);
        startEnd = tmp[0] == 's';
        // Extract time unit
        pos = tmp.find(':');
        timeUnit = stoi(tmp.substr(pos + 1));
        // Add first function execution
        stack[0] = {function, startEnd};

        // Parse remaining logs
        for(uint i = 1; i < logs.size(); i++){
            // Parse log
            // Extract function
            pos = logs[i].find(':');
            function = stoi(logs[i].substr(0, pos));
            // Extract if start or end
            tmp = logs[i].substr(pos + 1);
            startEnd = tmp[0] == 's';
            // Extract time unit
            pos = tmp.find(':');
            timeUnit = stoi(tmp.substr(pos + 1));

            // Update the time appropriately
            if(prevTimeUnitStartEnd && startEnd){
                result[stack[indexTop].first] += timeUnit - prevTimeUnit;
                prevTimeUnitStartEnd = true;
            } else if(prevTimeUnitStartEnd && !startEnd){
                result[stack[indexTop].first] += timeUnit - prevTimeUnit + 1;
                prevTimeUnitStartEnd = false;
            } else if(!prevTimeUnitStartEnd && startEnd){
                if(indexTop >= 0){
                    result[stack[indexTop].first] += timeUnit - prevTimeUnit - 1;
                }
                prevTimeUnitStartEnd = true;
            } else if(!prevTimeUnitStartEnd && !startEnd){
                result[stack[indexTop].first] += timeUnit - prevTimeUnit;
                prevTimeUnitStartEnd = false;
            }


            // Add or remove the function from the stack as appropriate
            if(startEnd){
                stack[indexTop + 1] = {function, startEnd};
                indexTop++;
            } else {
                indexTop--;
            }

            // Move the previous time unit to the one here
            prevTimeUnit = timeUnit;
        }

        return result;
    }

    void test_exclusiveTime(){
        //----- INITIALIZATIONS -----
        vector<string> logs;
        vector<int> exp;
        vector<int> res;
        bool validation;
        int indexDiff;

        // Test 1
        logs = {"0:start:0","1:start:2","1:end:5","0:end:6"};
        exp = {3, 4};
        res = exclusiveTime(2, logs);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 2
        logs = {"0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"};
        exp = {8};
        res = exclusiveTime(1, logs);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 2: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 3
        logs = {"0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"};
        exp = {7,1};
        res = exclusiveTime(2, logs);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 3: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 4
        logs = {"0:start:0","0:start:2","0:end:5","1:start:7","1:end:7","0:end:8"};
        exp = {8,1};
        res = exclusiveTime(2, logs);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 4: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test Case 5
        logs = {"0:start:0","0:end:0","1:start:1","1:end:1","2:start:2","2:end:2","2:start:3","2:end:3"};
        exp = {1,1,2};
        res = exclusiveTime(3, logs);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 5: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    You are given an integer array prices where prices[i] is the price of the ith item in a shop.

    There is a special discount for items in the shop. If you buy the ith item, then you will receive a discount equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <= prices[i]. Otherwise, you will not receive any discount at all.

    Return an integer array answer where answer[i] is the final price you will pay for the ith item of the shop, considering the special discount.
    */
    vector<int> finalPrices(vector<int>& prices) {
        //----- INITIALIZATIONS -----
        // Final result
        vector<int> result(prices);
        // Stack of indices of the prices for potential discount
        vector<int> stack(prices.size());
        // Size of the stack
        uint stackSize = 0;
        stack[stackSize] = 0;
        stackSize++;

        //----- ALGORITHM -----
        for(uint i = 1; i < prices.size(); i++){
            // Apply discount
            while(stackSize > 0 && prices[stack[stackSize - 1]] >= prices[i]){
                result[stack[stackSize - 1]] = prices[stack[stackSize - 1]] - prices[i];
                stackSize--;
            }
            
            // Add price to the stack
            stack[stackSize] = i;
            stackSize++;
        }

        return result;
    }

    void test_finalPrices(){
        //----- INITIALIZATIONS -----
        vector<int> input;
        vector<int> exp;
        vector<int> res;
        bool validation;
        int indexDiff;

        //----- TESTS -----
        // Test 1
        input = {8,4,6,2,3};
        exp = {4,2,4,2,3};
        res = finalPrices(input);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 2
        input = {1,2,3,4,5};
        exp = {1,2,3,4,5};
        res = finalPrices(input);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 2: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 3
        input = {10,1,1,6};
        exp = {9,0,1,6};
        res = finalPrices(input);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 3: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

    Idea: put items on the stack if they don't meet the condition and pop items of the stack if they do
    */
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        //----- INITIALIZATIONS -----
        // Result array
        vector<int> result(temperatures.size());
        for(uint i = 0; i < result.size(); i++){
            result[i] = 0;
        }
        // Stack of the indices of the temps that need to be checked
        vector<int> stack(temperatures.size());
        // Size of the stack
        uint stackSize = 0;
        stack[stackSize] = 0;
        stackSize++;

        //----- ALGORITHM -----
        for(uint i = 1; i < temperatures.size(); i++){
            // Remove temps
            while(stackSize > 0 && temperatures[stack[stackSize - 1]] < temperatures[i]){
                result[stack[stackSize - 1]] = i - stack[stackSize - 1];
                stackSize--;
            }

            // Add index of current temp to stack
            stack[stackSize] = i;
            stackSize++;
        }

        return result;
    }

    void test_dailyTemperatures(){
        //----- INITIALIZATIONS -----
        vector<int> input;
        vector<int> exp;
        vector<int> res;
        bool validation;
        int indexDiff;

        //----- TESTS -----
        // Test 1
        input = {73,74,75,71,69,72,76,73};
        exp = {1,1,4,2,1,1,0,0};
        res = dailyTemperatures(input);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 1: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 2
        input = {30,40,50,60};
        exp = {1,1,1,0};
        res = dailyTemperatures(input);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 2: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }

        // Test 3
        input = {30,60,90};
        exp = {1,1,0};
        res = dailyTemperatures(input);

        // Check elements of vector
        validation = exp.size() == res.size();
        for(uint i = 0; i < res.size() && validation; i++){
            if(exp[i] != res[i]){
                indexDiff = i;
                validation = false;
            }
        }

        // Print results of test
        cout << "Test 3: ";
        if(validation){
            cout << "success." << endl;
        } else {
            cout << "failure. Different at " << indexDiff << " Expected: " << exp[indexDiff] << " Result: " << res[indexDiff] << endl;
        }
    }

    /*
    Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
    */
    int largestRectangleArea(vector<int>& heights) {
        //----- INITIALIZATIONS -----
        // Result
        int maxArea = -1;
        // Array of width's of the rectangle
        vector<int> width(heights.size());
        for(uint i = 0; i < width.size(); i++){
            width[i] = 0;
        }
        // Stack of the indices of the temps that need to be checked
        vector<int> stack(heights.size());
        // Size of the stack
        uint stackSize = 0;
        stack[stackSize] = 0;
        stackSize++;

        // Find the maximum width to the right
        for(uint i = 1; i < heights.size(); i++){
            // Remove elements from the stack if appropriate
            while(stackSize > 0 && heights[i] < heights[stack[stackSize - 1]]){
                width[stack[stackSize - 1]] = i - stack[stackSize - 1];
                stackSize--;
            }

            // Add element to the stack
            stack[stackSize] = i;
            stackSize++;
        }
        while(stackSize > 0){
            width[stack[stackSize - 1]] = heights.size() - stack[stackSize - 1];
            stackSize--;
        }

        // Find the maximum width to the left
        stack[stackSize] = heights.size() - 1;
        stackSize = 1;
        for(int i = heights.size() - 2; i >= 0; i--){
            // Remove elements from the stack if appropriate
            while(stackSize > 0 && heights[i] < heights[stack[stackSize - 1]]){
                width[stack[stackSize - 1]] += stack[stackSize - 1] - i - 1;
                stackSize--;
            }

            // Add element to the stack
            stack[stackSize] = i;
            stackSize++;
        }

        while(stackSize > 0){
            width[stack[stackSize - 1]] += stack[stackSize - 1];
            stackSize--;
        }

        // Calculate the height
        maxArea = width[0] * heights[0];
        for(uint i = 1; i < heights.size(); i++){
            if(width[i] * heights[i] > maxArea){
                maxArea = width[i] * heights[i]; 
            }
        }

        return maxArea;
    }

    void test_largestRectangleArea(){
        //----- INITIALIZATIONS -----
        vector<int> input;
        int exp;
        int res;

        //----- TESTS -----
        // Test 1
        input = {2,1,5,6,2,3};
        exp = 10;
        res = largestRectangleArea(input);

        // Print results of test
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 2
        input = {2,4};
        exp = 4;
        res = largestRectangleArea(input);

        // Print results of test
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 3
        input = {5,5,1,7,1,1,5,2,7,6};
        exp = 12;
        res = largestRectangleArea(input);

        // Print results of test
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.

    The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:

        If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.
        Otherwise, they will leave it and go to the queue's end.

    This continues until none of the queue students want to take the top sandwich and are thus unable to eat.

    You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the i​​​​​​th sandwich in the stack (i = 0 is the top of the stack) and students[j] is the preference of the j​​​​​​th student in the initial queue (j = 0 is the front of the queue). Return the number of students that are unable to eat.
    
    Initialy I thought this might be simplified as a counting problem, because the students cycle infinitely. However, there can be so many of a type of sandwhich in a row that students won't be able to work though them. For example:
        students = {1,1,1,1,1};
        sandwiches = {1,0,1};
    There is no student to take the circular sandwich, so the square sandwich is stranded under it (stack) and 4 students would go hungry.

    */
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        //----- INITIALIZATIONS -----
        // Nominally would want to make a copy of students to preserve the original data
        // Pass by reference - not constant reference though
        int queueFront = 0;
        int queueLen = students.size();
        // First student sent to the back of the line
        int sentBackCounter = -1;
        // Current sandwhich on top of the stack
        uint currSandwich = 0;
        
        //----- ALGORITHM -----
        // Three exit conditions:
        // - All of the students are fed
        // - No more sandwiches
        // - No student wants the top sandwhich
        while(queueLen > 1 && currSandwich != sandwiches.size() && sentBackCounter != queueLen){
            if(students[queueFront] == sandwiches[currSandwich]){
                // If the student wants the sandwhich remove them and the sandwhich from the queue
                students.erase(students.begin() + queueFront);
                queueLen--;
                currSandwich++;
                // Reset the sent back counter
                sentBackCounter = 0;
                // Fix the front of the queue
                queueFront = queueFront % queueLen;
            } else {
                // Track how many students have been sent back
                sentBackCounter++;
                // Move to the next student
                queueFront = (queueFront + 1) % queueLen;
            }
            
        }

        // Last student
        if(queueLen == 1 && students[0] == sandwiches[currSandwich]){
            queueLen--;
        }

        return queueLen;
    }
    
    void test_countStudents(){
        //----- INITIALIZATIONS -----
        vector<int> input1;
        vector<int> input2;
        int exp;
        int res;

        //----- TESTS -----
        // Test 1
        input1 = {1,1,0,0};
        input2 = {0,1,0,1};
        exp = 0;
        res = countStudents(input1, input2);

        // Print results of test
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 2
        input1 = {1,1,1,0,0,1};
        input2 = {1,0,0,0,1,1};
        exp = 3;
        res = countStudents(input1, input2);

        // Print results of test
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 3
        input1 = {1,1,1,1,1,1};
        input2 = {1,0,1};
        exp = 5;
        res = countStudents(input1, input2);

        // Print results of test
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    There are n people in a line queuing to buy tickets, where the 0th person is at the front of the line and the (n - 1)th person is at the back of the line.

    You are given a 0-indexed integer array tickets of length n where the number of tickets that the ith person would like to buy is tickets[i].

    Each person takes exactly 1 second to buy a ticket. A person can only buy 1 ticket at a time and has to go back to the end of the line (which happens instantaneously) in order to buy more tickets. If a person does not have any tickets left to buy, the person will leave the line.

    Return the time taken for the person initially at position k (0-indexed) to finish buying tickets.
    
    This seems like it can be solved without a queue
    */
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        //----- INITIALIZATIONS -----
        // Total amount of time needed
        int total = 0;
        
        //----- ALGORITHM -----
        // People before person k
        for(int i = 0; i <= k; i++){
            total += tickets[i] <= tickets[k] ? tickets[i] : tickets[k];
        }
        
        // People after person k
        for(uint i = k + 1; i < tickets.size(); i++){
            total += (tickets[i] < tickets[k] ? tickets[i] : tickets[k] - 1); 
        }

        return total;
    }

    void test_timeRequiredToBuy(){
        //----- INITIALIZATIONS -----
        vector<int> input1;
        int input2;
        int exp;
        int res;

        //----- TESTS -----
        // Test 1
        input1 = {2,3,2};
        input2 = 2;
        exp = 6;
        res = timeRequiredToBuy(input1, input2);

        // Print results of test
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 2
        input1 = {5,1,1,1};
        input2 = 0;
        exp = 8;
        res = timeRequiredToBuy(input1, input2);

        // Print results of test
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    void test_MyQueue(){
        MyQueue myQueue = MyQueue();
        myQueue.push(1); // queue is: [1]
        myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
        cout << myQueue.peek() << " (1)" << endl; // return 1
        cout << myQueue.pop() << " (1)"<< endl; // return 1, queue is [2]
        cout << myQueue.empty() << " (0/false)"<< endl; // return false
    }

};

int main(){
    Solution mySolution;
    mySolution.test_MyQueue();
    return 0;
}

