#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Definition for singly-linked list.
// Used for the addTwoNumbers problem
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

 // Delete the list
void deleteListNode(ListNode* l1){
    if(l1){
        if(l1->next){
            deleteListNode(l1->next);
        }
        delete(l1);
    }
}

// Print the list
void printListNode(ListNode* l1){
    if(l1){
        cout << "[" << l1->val;
        ListNode* curr = l1;
        while(curr->next){
            curr = curr->next;
            cout << "," << curr->val;
        }
        cout << "]";
    } else {
        cout << "[]";
    }
}

// Check for equality
bool isEqual(ListNode* l1, ListNode* l2){
    ListNode* curr1 = l1;
    ListNode* curr2 = l2;
    if((l1 && !l2) || (!l1 && l2)){
        return false;
    }

    while(curr1 && curr2){
        if(curr1->val != curr2->val){
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return true;
}

// Create a linked list from the vector provided
ListNode* createLL(vector<int> list){
    ListNode* newList = nullptr;
    if(list.size() == 0){
        return nullptr;
    }

    newList = new ListNode();
    ListNode* currNode = newList;
    for(uint i = 0; i < list.size() - 1; i++){
        currNode->val = list[i];
        currNode->next = new ListNode();
        currNode = currNode->next;
    }
    currNode->val = list[list.size() - 1];

    return newList;
}
 
class Solution {
public:
    /*
    Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

    Symbol       Value
    I             1
    V             5
    X             10
    L             50
    C             100
    D             500
    M             1000

    For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

    Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

        I can be placed before V (5) and X (10) to make 4 and 9. 
        X can be placed before L (50) and C (100) to make 40 and 90. 
        C can be placed before D (500) and M (1000) to make 400 and 900.

    Given a roman numeral, convert it to an integer.

    Constraints:
    1 <= s.length <= 15
    s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
    It is guaranteed that s is a valid roman numeral in the range [1, 3999].
    
    Examples:
    I       X       C
    II      XX      CC
    III     XXX     CCC
    IV      XL      CD
    V       L       D
    VI      LX      DC
    VII     LXX     DCC
    VIII    LXXX    DCCC
    IX      XC      CM
    X       C       M
    */
    int romanToInt(string s) {
        int res = 0;
        for(uint i = 0; i < s.size(); i++){
            switch(s[i]){
                case 'M':
                    res += 1000;
                    break;
                case 'D':
                    res += 500;
                    break;
                case 'C':
                    if(i + 1 < s.size() && (s[i + 1] == 'M' || s[i + 1] == 'D')){
                        res -= 100;
                    } else {
                        res += 100;
                    }
                    break;
                case 'L':
                    res += 50;
                    break;
                case 'X':
                    if(i + 1 < s.size() && (s[i + 1] == 'C' || s[i + 1] == 'L')){
                        res -= 10;
                    } else {
                        res += 10;
                    }
                    break;
                case 'V':
                    res += 5;
                    break;
                case 'I':
                    if(i + 1 < s.size() && (s[i + 1] == 'X' || s[i + 1] == 'V')){
                        res -= 1;
                    } else {
                        res += 1;
                    }
                    break;
                default:
                    cerr << "romanToInt: Invalid character in string " << s << endl;
                    break;
            }
        }

        return res;
    }

    void test_romanToInt(){
        int exp = 3;
        int res = romanToInt("III"); 
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = 17;
        res = romanToInt("XVII"); 
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    Two Sums

    Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

    You may assume that each input would have exactly one solution, and you may not use the same element twice.

    You can return the answer in any order.

    Constraints:
    2 <= nums.length <= 104
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target <= 10^9
    Only one valid answer exists.

    Solution notes:
    - Retry with hash table - unordered_map - should be faster and should be able to do it in one pass
        - Add first element to hash
        - Check hash to see if target - nums[i] is in the hash table already, if not add this element to the hash table
    - Return early hack - return {};, in other words return nonsense. This prevents the need for the use of a flag variable


    */
    vector<int> twoSum0(vector<int>& nums, int target) {
        //----- INITIALIZATION -----
        // Exit flag
        bool done = false;
        // Result vector
        vector<int> result = {0, 0};

        //----- ALGORITHM -----
        for(uint i = 0; i < nums.size() - 1 && !done; i++){
            for(uint j = i + 1; j < nums.size() && !done; j++){
                if(nums[i] + nums[j] == target){
                    result[0] = i;
                    result[1] = j;
                    done = true;
                }
            }
        }

        return result;
    }

    // Hash table version
    vector<int> twoSum(vector<int>& nums, int target) {
        //----- INITIALIZATION -----
        // Hash table to store the observed numbers
        unordered_map<int, int> table;

        //----- ALGORITHM -----
        // Use number as key and index as value
        table[nums[0]] = 0;
        for(int i = 1; i < nums.size(); i++){
            int complement = target - nums[i];
            // Check if the table has the complement of the current number so that when added together they make the target
            if(table.count(complement)){
                return {table[complement], i};
            } else {
                // Add the number-index pair to the hash table
                table[nums[i]] = i;
            }
        }

        // No solution found - should never be reached
        return {};
    }

    void test_twoSum(){
        vector<int> exp = {0, 1};
        vector<int> input = {2, 7, 11, 15};
        vector<int> res = twoSum(input, 9);
        cout << "Test 1: ";
        if((exp[0] == res[0] && exp[1] == res[1]) || (exp[0] == res[1] && exp[1] == res[0])){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: [" << exp[0] << "," << exp[1] << "] Result: [" << res[0] << "," << res[1] << "]" << endl;
        }

        exp = {1, 2};
        input = {3, 2, 4};
        res = twoSum(input, 6);
        cout << "Test 2: ";
        if((exp[0] == res[0] && exp[1] == res[1]) || (exp[0] == res[1] && exp[1] == res[0])){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: [" << exp[0] << "," << exp[1] << "] Result: [" << res[0] << "," << res[1] << "]" << endl;
        }

        exp = {0, 1};
        input = {3, 3};
        res = twoSum(input, 6);
        cout << "Test 2: ";
        if((exp[0] == res[0] && exp[1] == res[1]) || (exp[0] == res[1] && exp[1] == res[0])){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: [" << exp[0] << "," << exp[1] << "] Result: [" << res[0] << "," << res[1] << "]" << endl;
        }
    }

    /*
    Add the two numbers in the linked lists provided. Digits are given in reverse order.

    Constraints:
    The number of nodes in each linked list is in the range [1, 100].
    0 <= Node.val <= 9
    It is guaranteed that the list represents a number that does not have leading zeros.
    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // REFACTOR: Solution is likely refactorable, given the code for handling the tails of each list is largely the same as the code for when the lists both have digits to add

        //----- EDGE CASES -----
        // Given two empty lists
        if(!l1 && !l2){
            return nullptr;
        }

        //----- INITIALIZATION -----
        // Linked list being constructed to hold the sum
        ListNode* newList = new ListNode();
        // Pointer to current node in newList
        ListNode* currNewList = newList;
        // Flag for reaching the end of the first linked list
        bool endOf1 = l1 == nullptr;
        // Pointer to the current node in l1
        ListNode* currNode1 = l1;
        // Flag for reaching the end of the second linked list
        bool endOf2 = l2 == nullptr;
        // Pointer to the current node in l2
        ListNode* currNode2 = l2;
        // Carry a one flag
        int carryOne = 0;
        // Temporary variable for holding the current sum
        int temp;

        //----- ALGORITHM -----
        // Loop through until the end of one of the numbers is reached
        while(!endOf1 && !endOf2){
            // Do addition
            temp = currNode1->val + currNode2->val + carryOne;
            // Carry the one
            if(temp > 9){
                carryOne = 1;
                temp -= 10;
            } else {
                 carryOne = 0;
            }

            // Update the value
            currNewList->val = temp;

            // Move to the next node in each number
            if(currNode1->next){
                currNode1 = currNode1->next;
            } else {
                endOf1 = true;
            }
            if(currNode2->next){
                currNode2 = currNode2->next;
            } else {
                endOf2 = true;
            }

            // Create a next node in the list if appropriate
            if(carryOne || !endOf1 || !endOf2){
                currNewList->next = new ListNode();
                currNewList = currNewList->next;
            }
        }

        // Complete tail of the first list
        if(endOf2){
            while(!endOf1){
                // Add as appropriate
                if(carryOne){
                    temp = currNode1->val + carryOne;
                    if(temp > 9){
                        carryOne = 1;
                        temp -= 10;
                    } else {
                        carryOne = 0;
                    }
                } else {
                    temp = currNode1->val;
                }

                // Put into new number
                currNewList->val = temp;

                // Move node pointer
                if(currNode1->next){
                    currNode1 = currNode1->next;
                } else {
                    endOf1 = true;
                }

                // Make new node if appropriate
                if(carryOne || !endOf1 || !endOf2){
                    currNewList->next = new ListNode();
                    currNewList = currNewList->next;
                }
            }
        }

        // Complete tail of the second list
        if(endOf1){
            while(!endOf2){
                // Add as appropriate
                if(carryOne){
                    temp = currNode2->val + carryOne;
                    if(temp > 9){
                        carryOne = 1;
                        temp -= 10;
                    } else {
                        carryOne = 0;
                    }
                } else {
                    temp = currNode2->val;
                }

                // Put into new number
                currNewList->val = temp;

                // Move node pointer
                if(currNode2->next){
                    currNode2 = currNode2->next;
                } else {
                    endOf2 = true;
                }

                // Make new node if appropriate
                if(carryOne || !endOf1 || !endOf2){
                    currNewList->next = new ListNode();
                    currNewList = currNewList->next;
                }
            }
        }

        // Add final leading 1 if needed
        if(carryOne && endOf1 && endOf2){
            currNewList->val = 1;
        }

        return newList;
    }

    void test_ListNodeDiagnostics(){
        vector<int> temp = {0, 1, 3};
        // Test Create LL
        ListNode* l1 = createLL(temp);

        // Test Print LL
        cout << "List: ";
        printListNode(l1);
        cout << endl;

        // Test equality
        ListNode* l2 = createLL(temp);
        cout << "Two equal lists: ";
        if(isEqual(l1, l2)){
            cout << "success." << endl;
        } else {
            cout << "failure." << endl;
        }
        deleteListNode(l2);
        l2 = nullptr;

        cout << "One empty list: ";
        if(!isEqual(l1, l2)){
            cout << "success." << endl;
        } else {
            cout << "failure." << endl;
        }
        
        temp.clear();
        temp = {0, 1, 2, 3};
        l2 = createLL(temp);
        cout << "Different sized lists: ";
        if(!isEqual(l1, l2)){
            cout << "success." << endl;
        } else {
            cout << "failure." << endl;
        }

        // Clean up - test delete with valgrind
        deleteListNode(l1);
        deleteListNode(l2);
    }

    void test_addTwoNumbers(){
        // Test 1
        vector<int> temp = {0, 1, 3};
        ListNode* l1 = createLL(temp);
        temp.clear();

        temp = {3, 2, 1};
        ListNode* l2 = createLL(temp);
        temp.clear();

        temp = {3, 3, 4};
        ListNode* exp = createLL(temp);
        temp.clear();

        ListNode* res = addTwoNumbers(l1, l2);
        cout << "Test 1: ";
        if(isEqual(exp, res)){
            cout << "success" << endl;
        } else {
            cout << "Expected: ";
            printListNode(exp);
            cout << " Result: ";
            printListNode(res);
            cout << endl;
        }

        // Test 2
        deleteListNode(l1);
        deleteListNode(l2);
        deleteListNode(exp);
        deleteListNode(res);

        temp = {1, 1, 1};
        l1 = createLL(temp);
        temp.clear();

        temp = {9, 9, 9};
        l2 = createLL(temp);
        temp.clear();

        temp = {0, 1, 1, 1};
        exp = createLL(temp);
        temp.clear();

        res = addTwoNumbers(l1, l2);
        cout << "Test 2: ";
        if(isEqual(exp, res)){
            cout << "success" << endl;
        } else {
            cout << "Expected: ";
            printListNode(exp);
            cout << " Result: ";
            printListNode(res);
            cout << endl;
        }

        // Final memory clean up
        deleteListNode(l1);
        deleteListNode(l2);
        deleteListNode(exp);
        deleteListNode(res);
    }

    string addBinary(string a, string b) {
        // REFACTOR: because of pass by copy, algorithm could be made more efficient by doing in place editing of the variable
        
        //----- INITIALIZATION -----
        // The final result
        string res;
        // Carry the one
        bool carryOne = false;

        //----- ALGORITHM -----
        // Concatenate zeroes
        if(a.size() > b.size()){
            b = string(a.size() - b.size(), '0') + b;
            res = string(a.size(), '0');
        } else {
            a = string(b.size() - a.size(), '0') + a;
            res = string(b.size(), '0');
        }

        // Add
        for(int i = a.size() - 1; i >= 0; i--){
            if(carryOne){
                if(a[i] == '1' && b[i] == '1'){
                    res[i] = '1';
                } else if(a[i] == '0' && b[i] == '1'){
                    res[i] = '0';
                } else if(a[i] == '1' && b[i] == '0'){
                    res[i] = '0';
                } else if(a[i] == '0' && b[i] == '0'){
                    carryOne = false;
                    res[i] = '1';
                }
            } else {
                if(a[i] == '1' && b[i] == '1'){
                    carryOne = true;
                    res[i] = '0';
                } else if(a[i] == '0' && b[i] == '1'){
                    res[i] = '1';
                } else if(a[i] == '1' && b[i] == '0'){
                    res[i] = '1';
                } else if(a[i] == '0' && b[i] == '0'){
                    res[i] = '0';
                }
            }
        }

        // Deal with leading 1
        if(carryOne){
            res = '1' + res;
        }
        
        return res;
    }

    void test_addBinary(){
        // Test 1
        string a = "11";
        string b = "11";
        string exp = "110";
        string res = addBinary(a, b);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        // Test 2
        a = "11";
        b = "1";
        exp = "100";
        res = addBinary(a, b);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    bool isPalindrome(int x) {
        // REFACTOR - reverse the number and check for equality
        
        //----- EDGE CASES -----
        // Per the spec - negative numbers can't be palindromes
        if(x < 0){
            return false;
        }

        //----- ALGORITHM -----
        // Use the built-in to_string algorithm to convert to a string and then check
        string num = to_string(x);
        for(int i = 0; i < num.size() / 2; i++){
            if(num[i] != num[num.size() - i - 1]){
                return false;
            }
        }

        return true;
    }

    void test_isPalindrome(){
        bool exp = true;
        bool res = isPalindrome(121);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = false;
        res = isPalindrome(-121);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = false;
        res = isPalindrome(10);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }
    /*
    You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

    Find two lines that together with the x-axis form a container, such that the container contains the most water.

    Return the maximum amount of water a container can store.

    Note the amount of water that any pair of lines can store is:
    water = min(height[i], height[j]) * abs(i - j)

    Algorithm 1: for each value, there is a maximum water level based on it's positioning. Look for the first value from the left and the first value from the right that is bigger than the current height - that will give the water level.
    [3 1 4 2]
    3 - nothing to the left, 4, is the first value larger than it, so it's largest paired value is 3-4 -> 6
    1 - 3 to the left, 2 to the right, 1-2 -> 2
    4 - nothing larger than it
    2 - nothing to the right, 3 to the left, so paired height 2-3 -> 3*2 -> 6
    6 is the max
    This is O(n^2) it organizes the data in such a way that it checks all the values it needs to.
    */
    
    int maxArea_v1(vector<int>& height) {
        // REFACTOR: make code more succinct
        //----- EDGE CASES -----
        if(height.size() < 2){
            return -1;
        }

        if(height.size() == 2){
            return height[0] < height[1] ? height[0] : height[1];
        }
        
        //----- INITIALIZATION -----
        // Current index
        int i = 0;
        // Current max water amount
        int maxWater = 0;
        // Current value of water amount
        int currWater = 0;

        // Boundary Case: Left-most value
        // Only need to consider values from the right
        int j = height.size() - 1;
        while(height[i] > height[j] && j > i){
            j--;
        }
        maxWater = height[i] * (j - i);

        // Middle-values
        for(i = 1; i < height.size() - 1; i++){
            j = height.size() - 1;
            while(height[i] > height[j] && j > i){
                j--;
            }
            currWater = height[i] * (j - i);
            maxWater = currWater > maxWater ? currWater : maxWater;

            j = 0;
            while(height[i] > height[j] && j < i){
                j++;
            }
            currWater = height[i] * (i - j);
            maxWater = currWater > maxWater ? currWater : maxWater;
        }

        // Boundary Case: Right-most value
        j = 0;
        while(height[i] > height[j] && j < i){
            j++;
        }
        currWater = height[i] * (i - j);

        return currWater > maxWater ? currWater : maxWater;
    }

    /* 
    Algorithm 2: two pointer method
    
    Premise - start at outer most rectangle, area can only increase if height increases as we move inward. Alternate moving pointers inward left and right based on which one is smaller, until pointers meet in the middle.
    
    So we find which is smaller left or right, the area, is size * minHeight, then we move inward. An example will illustrate the algorithm:
    index:  [0,1,2,3,4,5,6,7,8]
    values: [1,8,6,2,5,4,8,3,7]
    Start: left is 1, right is 7 - area is min(1, 7) * (8 - 0) = 8
    - Move left index because it is the smaller of the two.
    - Look at 8 - 8 > 7 -> new max area potential: min(8, 7) * (8 - 1) = 49 -> new max area
    - Also, 8 > 7 so start moving right index left
    - 7 > 3, but 7 < 8 -> new max area potential: min(8, 8) * (6 - 1) = 40 not new max area
    - Keep going - either move left or right, algorithm is agnostic because they are equal.
        - NOTE: the algorithm isn't done, as there could be big values in the middle [1,2,900,900,1,2] would not look at the 900's and would get an incorrect answer if we stopped at 2 == 2 so done
    - 8 is bigger than all the remaining numbers so eventually left == right
    - The algorithm is thus complete and the max value is 49

    
    */
    int maxArea(vector<int>& height){
        //----- EDGE CASES -----
        if(height.size() < 2){
            return -1;
        }

        if(height.size() == 2){
            return height[0] < height[1] ? height[0] : height[1];
        }
        
        //----- INITIALIZATION -----
        // Left Index
        int leftIndex = 0;
        // Current value of height on the left
        int currLeftHeight = height[leftIndex];
        // Right Index
        int rightIndex = height.size() - 1;
        // Current value of height on the left
        int currRightHeight = height[rightIndex];
        // Maximum area value - calculate the first value
        int maxArea = (currLeftHeight < currRightHeight ? currLeftHeight : currRightHeight) * rightIndex;
        // Calculated area value
        int currArea;

        //----- ALGORITHM -----
        while(leftIndex < rightIndex){
            if(currLeftHeight < currRightHeight){
                // Move left index right
                while(height[leftIndex] <= currLeftHeight && leftIndex < rightIndex){
                    leftIndex++;
                }
                if(leftIndex < rightIndex){
                    currLeftHeight = height[leftIndex];
                }
            } else {
                // Move right index left
                while(height[rightIndex] <= currRightHeight && leftIndex < rightIndex){
                    rightIndex--;
                }
                if(leftIndex < rightIndex){
                    currRightHeight = height[rightIndex];
                }
            }

            // Update maximum
            currArea = (currLeftHeight < currRightHeight ? currLeftHeight : currRightHeight) * (rightIndex - leftIndex);
            if(currArea > maxArea){
                maxArea = currArea;
            }

        }

        return maxArea;
    }

    void test_maxArea(){
        vector<int> height = {1,8,6,2,5,4,8,3,7};
        int exp = 49;
        int res = maxArea(height);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    Convert numbers 1-3999 to roman numerals
    */
    string intToRoman(int num) {
        //----- INITIALIZATION -----
        string res = "";
        
        //----- ALGORITHM -----
        // Thousands
        if(num >= 3000){
            res = "MMM";
        } else if(num >= 2000){
            res = "MM";
        } else if(num >= 1000) {
            res = "M";
        }
        num = num % 1000;

        // Hundreds
        if(num >= 900){
            res = res + "CM";
        } else if(num >= 800){
            res = res + "DCCC";
        } else if(num >= 700){
            res = res + "DCC";
        } else if(num >= 600){
            res = res + "DC";
        } else if(num >= 500){
            res = res + "D";
        } else if(num >= 400){
            res = res + "CD";
        } else if(num >= 300){
            res = res + "CCC";
        } else if(num >= 200){
            res = res + "CC";
        } else if(num >= 100){
            res = res + "C";
        }
        num = num % 100;

        // Tens
        if(num >= 90){
            res = res + "XC";
        }else if(num >= 80){
            res = res + "LXXX";
        } else if(num >= 70){
            res = res + "LXX";
        } else if(num >= 60){
            res = res + "LX";
        } else if(num >= 50){
            res = res + "L";
        } else if(num >= 40){
            res = res + "XL";
        } else if(num >= 30){
            res = res + "XXX";
        } else if(num >= 20){
            res = res + "XX";
        } else if(num >= 10){
            res = res + "X";
        }
        num = num % 10;

        // Ones
        if(num == 9){
            res = res + "IX";
        }else if(num == 8){
            res = res + "VIII";
        } else if(num == 7){
            res = res + "VII";
        } else if(num == 6){
            res = res + "VI";
        } else if(num == 5){
            res = res + "V";
        } else if(num == 4){
            res = res + "IV";
        } else if(num == 3){
            res = res + "III";
        } else if(num == 2){
            res = res + "II";
        } else if(num == 1){
            res = res + "I";
        }
        
        return res;
    }

    void test_intToRoman(){
        string exp = "MMMDCCXLIX";
        string res = intToRoman(3749);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "LVIII";
        res = intToRoman(58);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "MCMXCIV";
        res = intToRoman(1994);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    Convert a non-negative integer num to its English words representation.
    0 <= num <= 2^31 - 1 = 2,147,483,647 (Two Billion or so)
    */
    string numberToWords(int num) {
        //----- EDGE CASES -----
        if(num == 0){
            return "Zero";
        }

        //----- INITIALIZATION -----
        string res = "";

        // Billions
        if(num >= 2000000000){
            res = "Two Billion";
        } else if(num >= 1000000000){
            res = "One Billion";
        }
        num = num % 1000000000;

        // Millions
        if(num >= 1000000){
            if(res.size() != 0){
                res += " ";
            }
            res += numberToWordsUnderThousand(num / 1000000);
            res += " Million";
        }
        num = num % 1000000;
        
        
        // Thousands
        if(num >= 1000){
            if(res.size() != 0){
                res += " ";
            }
            res += numberToWordsUnderThousand(num / 1000);
            res += " Thousand";
        }
        num = num % 1000;

        // Below 1000
        if(num > 0){
            if(res.size() != 0){
                res += " ";
            }
            res += numberToWordsUnderThousand(num);
        }

        return res;
        
    }

    // Create a string from a number between 1 - 999
    string numberToWordsUnderThousand(int num){
        //----- INITIALIZATION -----
        string res = "";

        // Hundreds
        if(num >= 100){
            if(num >= 900){
                res = "Nine Hundred";
            } else if(num >= 800){
                res = "Eight Hundred";
            } else if(num >= 700){
                res = "Seven Hundred";
            } else if(num >= 600){
                res = "Six Hundred";
            } else if(num >= 500){
                res = "Five Hundred";
            } else if(num >= 400){
                res = "Four Hundred";
            } else if(num >= 300){
                res = "Three Hundred";
            } else if(num >= 200){
                res = "Two Hundred";
            } else {
                res = "One Hundred";
            }
        }

        // Trim leading digit
        num = num % 100;

        // Tens
        bool isTeen = false;
        if(num >= 10){
            if(res.size() != 0){
                res += " ";
            }

            if(num >= 90){
                res += "Ninety";
            } else if(num >= 80){
                res += "Eighty";
            } else if(num >= 70){
                res += "Seventy";
            } else if(num >= 60){
                res += "Sixty";
            } else if(num >= 50){
                res += "Fifty";
            } else if(num >= 40){
                res += "Forty";
            } else if(num >= 30){
                res += "Thirty";
            } else if(num >= 20){
                res += "Twenty";
            } else {
                // Special case for the teens
                isTeen = true;
            }
        }

        // Do the teens or move onto the ones
        if(isTeen){
            if(num == 19){
                res += "Nineteen";
            } else if(num == 18){
                res += "Eighteen";
            } else if(num == 17){
                res += "Seventeen";
            } else if(num == 16){
                res += "Sixteen";
            } else if(num == 15){
                res += "Fifteen";
            } else if(num == 14){
                res += "Fourteen";
            } else if(num == 13){
                res += "Thirteen";
            } else if(num == 12){
                res += "Twelve";
            } else if(num == 11){
                res += "Eleven";
            } else {
                res += "Ten";
            }
        } else {
            // Trim leading digit
            num = num % 10;
            if(num > 0 && res.size() != 0){
                res += " ";
            }

            // Ones
            if(num > 0){
                if(num == 9){
                    res += "Nine";
                } else if(num == 8){
                    res += "Eight";
                } else if(num == 7){
                    res += "Seven";
                } else if(num == 6){
                    res += "Six";
                } else if(num == 5){
                    res += "Five";
                } else if(num == 4){
                    res += "Four";
                } else if(num == 3){
                    res += "Three";
                } else if(num == 2){
                    res += "Two";
                } else {
                    res += "One";
                }
            }
        }

        return res;
    }

    void test_numberToWords(){
        string exp = "One Hundred Twenty Three";
        string res = numberToWords(123);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "Twelve Thousand Three Hundred Forty Five";
        res = numberToWords(12345);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven";
        res = numberToWords(1234567);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "One Hundred Twenty Three Million Four Hundred Fifty Six Thousand Seven Hundred Eighty Nine";
        res = numberToWords(123456789);
        cout << "Test 4: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety";
        res = numberToWords(1234567890);
        cout << "Test 5: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "One Billion Five Hundred Sixty Seven Thousand Eight Hundred Ninety";
        res = numberToWords(1000567890);
        cout << "Test 6: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    void test_numberToWordsUnderThousand(){
        string exp = "One Hundred Twenty Three";
        string res = numberToWordsUnderThousand(123);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "One Hundred Three";
        res = numberToWordsUnderThousand(103);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "One Hundred Thirteen";
        res = numberToWordsUnderThousand(113);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "One";
        res = numberToWordsUnderThousand(1);
        cout << "Test 4: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "Ten";
        res = numberToWordsUnderThousand(10);
        cout << "Test 5: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = "Eleven";
        res = numberToWordsUnderThousand(11);
        cout << "Test 6: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    A sequence of numbers is called an arithmetic progression if the difference between any two consecutive elements is the same.

    Given an array of numbers arr, return true if the array can be rearranged to form an arithmetic progression. Otherwise, return false.

    This smells like a mathematical proof.

    Examples:
    [1,2,3,4,5] is an arithmetic progression
    Differences: [-1,-1,-1,-1] total is -4
    [5,1,4,2,3] can be arranged to be an arithmetic progression
    Differences: [4,-3,2,-1] total is 2

    [3,5,1] can be arranged to be an arithmetic progression
    Differences: [-2,4] total is 2
    [1,3,5]
    Differences: [-2,-2] total is -4
    
    Parity problem?
    [1,3,1] cannot
    Differences: [-2, 2] total is 0
    [1,3,3] cannot
    Differences: [-2, 0] total is -2
    Not an even/odd difference parity thing

    To be an arithmetic progression, you have to be sorted. Otherwise, sign changes dictate that you can't be. Sorting is O(nln(n)), checking is O(n)
    */
    bool canMakeArithmeticProgression(vector<int>& arr) {
        //----- EDGE CASES -----
        if(arr.size() <= 2){
            return true;
        }

        //----- ALGORITHM -----
        // In order to be arithmetic progression, the elements must be in sorted order

        // Sort
        sort(arr.begin(), arr.end());

        // Validate
        int diff = arr[1] - arr[0];
        for(int i = 1; i < arr.size() - 1; i++){
            if(diff != arr[i + 1] - arr[i]){
                return false;
            }
        }

        return true;
    }

    void test_canMakeArithmeticProgression(){
        bool exp = true;
        vector<int> input = {3, 5, 1};
        bool res = canMakeArithmeticProgression(input);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = false;
        input = {1, 2, 4};
        res = canMakeArithmeticProgression(input);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    Given a positive integer n, find the pivot integer x such that:

    The sum of all elements between 1 and x inclusively equals the sum of all elements between x and n inclusively.

    Return the pivot integer x. If no such integer exists, return -1. It is guaranteed that there will be at most one pivot index for the given input.
    */
    int pivotInteger(int n) {
        //----- EDGE CASES -----
        if(n == 1){
            return 1;
        }

        //----- INITIALIZATION -----
        // Total value of sum of 1 to n
        int total = n * (n + 1) / 2;
        // Running total for comparison
        int runningTotal = 0;
        // Temporary variable for computation
        int temp;

        //----- ALGORITHM -----
        // Calculate the running total and check if the pivot condition is met
        // If the running total gets too big, quit, no pivot is possible
        for(int i = 1; i < n; i++){
            runningTotal += i;
            temp = total - runningTotal + i;
            if(temp == runningTotal){
                return i;
            } else if(temp < runningTotal){
                return -1;
            }
        }

        return -1;
    }

    void test_pivotInteger(){
        int exp = 6;
        int res = pivotInteger(8);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = 1;
        res = pivotInteger(1);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = -1;
        res = pivotInteger(4);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    int reverse(int x) {
        // Use longs to avoid int overflow
        long y = x;

        //----- EDGE CASES -----
        if(y < 10 && y > -10){
            return y;
        }
        
        //---- ALGORITHM -----
        // First make positive as to not deal with negative number weirdness when interacting with modulus
        bool isNegative = false;
        if(y < 0){
            isNegative = true;
            y = -y;
        }
        
        // Use modulus to construct number
        long res = y % 10;
        y = y / 10;
        while(y > 0){
            res = res * 10 + y % 10;
            y = y / 10;

            // Deal with integer overflow
            if(res > 2147483647){
                return 0;
            }
        }

        // Correct the sign
        if(isNegative){
            return -res;
        } else {
            return res;
        }
    }

    void test_reverse(){
        int exp = 123;
        int res = reverse(321);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = -123;
        res = reverse(-321);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = 21;
        res = reverse(120);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    An ugly number is a positive integer which does not have a prime factor other than 2, 3, and 5.

    Given an integer n, return true if n is an ugly number.
    */
    bool isUgly(int n){
        //----- EDGE CASES -----
        if(n <= 0){
            return false;
        }

        // Remove all factors of 2
        while(n % 2 == 0){
            n = n / 2;
        }

        // Remove all factors of 3
        while(n % 3 == 0){
            n = n / 3;
        }

        // Remove all factors of 5
        while(n % 5 == 0){
            n = n / 5;
        }

        return n == 1 || n == -1;
    }

    void test_isUgly(){
        bool exp = true;
        bool res = isUgly(6);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = true;
        res = isUgly(1);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = false;
        res = isUgly(14);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    bool isHappy(int n){
        //----- EDGE CASES -----
        if(n == 1){
            return true;
        }
        
        //----- INITIALIZATIONS -----
        // Hash to store which numbers have been visited in order to find loop
        unordered_map<int, int> numbersVisited;
        // Current value for the happy number test
        int currSum;
        // Flag for being done
        bool done = false;
        
        while(!done){
            // Calculate the test value
            currSum = 0;
            while(n > 0){
                currSum += (n % 10) * (n % 10);
                n = n / 10;
            }

            // Validate
            if(currSum == 1){
                // If happy
                done = true;
            } else if(numbersVisited.count(currSum) > 0){
                // If loop
                done = true;
            } else {
                // Otherwise add to hash
                numbersVisited.insert({currSum, 1});
                n = currSum;
            }
        }

        return currSum == 1;
    }

    void test_isHappy(){
        bool exp = true;
        bool res = isHappy(19);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = false;
        res = isHappy(2);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }

    /*
    Given a positive integer k, you need to find the length of the smallest positive integer n such that n is divisible by k, and n only contains the digit 1.

    Return the length of n. If there is no such n, return -1.

    Note: n may not fit in a 64-bit signed integer.

    This is some group theory BS, which is wild to me. Basically, numbers added together can add their moduli and numbers multipled together can multiply their moduli. So, since a number of all 1s is just a sum of powers of ten, we can just start moduling everything before it gets too big.
    
    Example:
    1 = 1
    11 = 1 + 10
    111 = 1 + 10 + 100 = (1 + 10) + 100(1)
    1111 = 1 + 10 + 100 + 1000 = (1 + 10) + 100(1 + 10)
    So 17 for example:
    1 % 17 = 1
    11 % 17 = 11
    100 % 17 = 15
    (100)^2 % 17 = 15^2 % 17 = 225 % 17 = 4
    Thus:
    1 % 17 = 1
    11 % 17 = 11
    111 % 17 = (11) + 15(1) = 26 = 9
    1111 % 17 = (11) + 15(1 + 10) = 9 + 15(10) = 6
    11111 % 17 = (11) + 15(11) + 4(1) = 6 + 4 = 10
    111111 % 17 = 10 + 40 = 50 % 17 = 16
    And so on. When do we stop though? Unless there is a mathematical proof I'm missing, there is no stop.

    Let's consider then the factors:
    1 -> 1
    11 -> 11
    111 -> 3 * 37
    1111 -> 11 * 101
    11111 -> 41 * 271
    111111 -> 3 * 7 * 11 * 13 * 37
    1111111 -> 239 * 4649

    Maybe composite moduli?

    Simpler solution
    11 = 10 * 1 + 1
    111 = 10 * 11 + 1
    So under modulus:
    111 % k = ((10 * (11 % k)) + 1) % k
    This is because it does not matter when we modulus - so composite modulus - which is a thing, I was doing it up there without realizing it.

    Now, we only need to execute up to k, why? There are at most k unique moduli, so if there is a cycle we'll either have repeats and not hit zero at the kth or we'll hit zero at the kth or before.
    */
    int smallestRepunitDivByK(int k) {
        //----- EDGE CASES/BASE CASES -----
        if(k == 1){
            return 1;
        } else if(k == 11) {
            return 2;
        } else if(k == 111) {
            return 3;
        } else if(k == 1111) {
            return 4;
        } else if(k % 2 == 0 || k % 5 == 0){
            return -1;
        }

        //----- INITIALIZATIONS -----
        // The number of 1s in the current number being tested
        int count;
        // The total current modulus
        int currMod;
        // The multiplicative factor on the next set of numbers
        int modulusFactor;
        // The multiplier based on the first power of 10 larger than k
        int multiplier;
        // Variable to keep track of the inner power of 10
        int power;
        // Flag variable
        bool done = false;

        // Calculate the multiplier and the initial count of 1s
        // Note: edge cases exclude 10, 100, 1000, 10000
        // Initial values
        count = 1;
        currMod = 1;
        multiplier = 10 % k;

        // Find the appropriate power
        power = 10;
        while(k > power){
            count++;
            currMod = currMod * 10 + 1;
            power *= 10;
        }
        multiplier = power % k;
        modulusFactor = multiplier;

        // Calculate the modulus until zero is found or arbitrary limit is reached
        while(!done){
            // Perform the inner factor modulus calculations
            power = 1;
            while(k > power){
                currMod = (currMod + modulusFactor * power) % k;
                power *= 10;
                count++;

                // Check mod
                if(currMod == 0){
                    cout << "I should be here" << endl;
                    return count;
                }
            }

            // Move modulus factor to next grouping
            modulusFactor = (modulusFactor * multiplier) % k;

            done = count > 100;
        }

        return -1;
    }

    // So much easier. I could cry T-T
    int smallestRepunitDivByKRefactor(int k) {
        //----- EDGE CASES/BASE CASES -----
        if(k == 1){
            return 1;
        } else if(k == 11) {
            return 2;
        } else if(k == 111) {
            return 3;
        } else if(k == 1111) {
            return 4;
        } else if(k % 2 == 0 || k % 5 == 0){
            return -1;
        }

        //----- INITIALIZATIONS -----
        int currRem = 1;
        for(int i = 0; i < k; i++){
            if(currRem == 0){
                return i + 1;
            } else {
                currRem = (currRem * 10 + 1) % k;
            }
        }

        return -1;
    }

    void test_smallestRepunitDivByK(){
        int exp = 1;
        int res = smallestRepunitDivByK(1);
        cout << "Test 1: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = -1;
        res = smallestRepunitDivByK(2);
        cout << "Test 2: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }

        exp = 3;
        res = smallestRepunitDivByK(3);
        cout << "Test 3: ";
        if(exp == res){
            cout << "success." << endl;
        } else {
            cout << "failure. Expected: " << exp << " Result: " << res << endl;
        }
    }
};

int main(){
    Solution mySolution;
    mySolution.test_smallestRepunitDivByK();
    return 0;
}