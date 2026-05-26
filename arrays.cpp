#include <vector>
#include <iostream>
#include <algorithm>

// For windows development
typedef unsigned int uint;

using namespace std;

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
        for(uint i = 0; i < n; i++){
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
        int i = 0;

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
};

int main(){
    Solution mySolution;
    mySolution.test_findDisappearedNumbers();
    return 0;
}

