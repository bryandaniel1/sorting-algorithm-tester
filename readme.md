# sorting-algorithm-tester

## Program Description

This C program allows the user to run a selected sorting algorithm to order the contents of a selected file and show the time elapsed for the operation. The algorithms to choose from are bubble sort, quick sort, and merge sort. The contents for the provided test files were found freely available online and modified to be nearly sorted. The program also allows for the creation of new test files by collecting user input or randomizing existing test files. The series of screenshots below show the difference in performance when sorting operations are performed on nearly sorted file contents and randomly ordered file contents.

The following picture shows the results of quick sort on a nearly sorted file of +58000 lines.

<figure>
  <img src="img/quick_sort.png" alt="Quick Sort"/>
  <figcaption>Figure1. Quick Sort Nearly Sorted</figcaption>
</figure><br>
<br>

The same file sorted by merge sort results in a shorter run time.

<figure>
  <img src="img/merge_sort.png" alt="Merge Sort"/>
  <figcaption>Figure 2. Merge Sort Nearly Sorted</figcaption>
</figure><br>
<br>

The nearly sorted file is randomized to create a new test file.

<figure>
  <img src="img/new_file_created.png" alt="New File"/>
  <figcaption>Figure 3. Test File Creation</figcaption>
</figure><br>
<br>

On the randomly ordered file, quick sort performs much faster.

<figure>
  <img src="img/quick_sort_on_random.png" alt="Quick Sort Random"/>
  <figcaption>Figure 4. Quick Sort Random</figcaption>
</figure><br>
<br>

Merge sort performs more slowly than quick sort on the fully randomized contents.

<figure>
  <img src="img/merge_sort_on_random.png" alt="Merge Sort Random"/>
  <figcaption>Figure 5. Merge Sort Random</figcaption>
</figure><br>
<br>
