# Theoretical part
## Exchange sort
The algorithm compares first element with all the elements after it and swaps them such that the smallest element has the smallest index.
Therefore, after the interior for loop finishes, the smallest element is on the first position.
Then the process repeats for every position until position `n-1`, the last element being the largest.
Therefore, for every position `i` the algorithm does `n-i` verifications and, if the condition inside the if statement is true, it also does `n-i` swaps.
So a constant number of operations executed `n-i` times.
Hence, the total number of operations is:
- best case (the list is already sorted)
  - `(n - 1) + (n - 2) + ... + 2 + 1 = n(n - 1) / 2` comparisons
  - `0` swaps
<br>
So we have `n(n - 1) / 2` operations.
Therefore, the complexity is `omega(n^2)`
- worst case (the list is sorted in reverse order)
  - `(n - 1) + (n - 2) + ... + 2 + 1 = n(n - 1) / 2` comparisons
  - `(n - 1) + (n - 2) + ... + 2 + 1 = n(n - 1) / 2` swaps
<br>
So we have `n(n - 1)` operations.
Therefore, the complexity is `O(n^2)`
- average case
<br>
The best case is Omega(n^2) and the worst case is O(n^2), hence the average case is Theta(n^2) <br><br>

## Strand sort
The algorithm takes the first element out of the list and adds it to an auxiliary list. 
Then it iterates through the initial list and for any element, if it is bigger than the last added element in the auxiliary list, 
it takes out that element from the initial list and adds it to the auxiliary list.
Then the auxiliary list is merged into the final list and the process repeats until the initial list is empty.
Hence, the total number of operations is:
- best case (the list is already sorted):
  - auxiliary list creation
    - `n` pushes into the auxiliary list
    - `n` pops from the initial list
    - `n-1` comparisons
  - merge
    - `n` pushes into the final list
<br> So the complexity is `Omega(n)`
- worst case (the list is sorted in reverse order)
  <br>`n` repetitions of the following process:
  - `1` push to the auxiliary list (the biggest number always on the first position): `O(1)`
  - merge the auxiliary list into the final list: `O(n+n) = O(n)`
<br> So the complexity is `O(n^2)`