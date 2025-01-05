[![Run tests](https://github.com/KKalamari/Project/actions/workflows/run-tests.yml/badge.svg)](https://github.com/KKalamari/Project/actions/workflows/run-tests.yml)
Project 2024-2025

Ισίδωρος Καλαμάρης 1115202000233 sdi2000233@di.uoa.gr

Κυριακή Καλαμάρη 1115202000255 sdi2000255@di.uoa.gr

Την main την τρέχουμε με make στον αρχικό κατάλογο και μετά με ./output/main k_num r_num a_num l_num ή make και μετά ./main στο output directory.

Τα tests στον φάκελο test με make run

Για greedysearch,Robust_ext και vamana Δημιουργούμε 2 matrixes:

.Το vecmatrix είναι οι ευκλείδιες αποστάσεις για κάθε ζεύγος node που υπάρχει στο database που διαβάζουμε (δηλαδή είναι 10000*10000 matrix)

.Το querymatrix είναι οι ευκλείδιες αποστάσεις για κάθε node του database με το xq που διαβάζουμε από το query αρχείο.

Ακούγονται ακριβά, αλλά στο vecmatrix εκμεταλλευόμαστε τη συμμετρία της ευκλείδιας και το query matrix είναι 10000*100. Μετά από τον αρχικό υπολογισμό έχουμε προσπέλαση στις αποστάσεις σε O(1) που φέρνει καλά αποτελέσματα.

Robust:

PickingP: Συνάρτηση που βάση την ήδη υπολογίσμενη απόσταση, διαλέγει από το candidateset το πιο κοντινο σημείο.

RobustPrune: Συνάρτηση στην οποία υλοποιέιται το pruning με τη βοήθεια της PickingP , euclidean distance.

Greedy:

unexplored nodes: Συνάρτηση η οποία ελέγχει πως το L περιέχει τουλάχιστον 1 κόμβο που δεν εχει γίνει explored.

unexplored node: Ίδια λογικη με την unexplored nodes αλλά για έναν συγκεκριμένο κόμβο.

addtoL: Συνάρτηση που προσθέτει τους γείτονες ενός κόμβου σε λίσταα L ταξινομημένα με βάση την απόσταση τους.

greedysearch: Συνάρτηση στην οποία υλοποιείται ο greedy αλγόριθμος με την χρήση των βοηθητικών συναρτήσεων και της ευκλείδειας απόστασης.

vamana :

medoid: Συνάρτηση που βρήσκει το medoid.

vamana_index_algorithm: Συναρτηση που φτιάχει τον γράφω vamana χρησιμοποιόντας τις συναρτήσεις medoid, greedysearch , RobustPrune.

Χρόνοι: (με flag -O3) Για α=1.1,k=100,L=150,R=16 τρέχει σε 5,30 λεπτά με πολύ καλό accuracy (σχεδόν όλα >95%) Για α=1, κ=50,L=100,R=20 τρέχει σε 2,30 λεπτά με recall=1 (και τα neighbors ανήκουν στο groundtruth) Για a=1.2,k=100,L_sizelist=120,R=14 2 λεπτά με καλό accuracy ( από τα 100 queries τα 95 είχαν παραπάνω από 90 κοινά στοιχεία)


##Παραδοτέο 2:

Υλοποιήθηκαν εκ νέου συναρτήσεις FilteredGreedySearch,FilteredRobustPrune και FilteredVamana και medoid.

FilteredVamana:
Η κεντρική ιδέα είναι πως χρησιμοποιούμε στη greedysearch set<pair<double,int>> ώστε να γίνεται κατευθείαν sorted το L με το κόμβο που απέχει το λιγότερο από αυτόν που ελέγχουμε αυτή τη στιγμή κάνωντας τον greedysearch πολύ πιο γρήγορο σε σχέση με το πρώτο παραδοτέο και κατ'επέκταση και τις υπόλοιπες συναρτήσεις. Η ευκλείδια απόσταση πάλι αποθηκεύεται και χρησιμοποιείται σε σταθερό χρόνο όποτε χρειάζεται.

StitchedVamana:
Χρησιμοποιήθηκαν οι συναρτήσεις του πρώτου παραδοτέου για την υλοποίση της, για αυτό και ο χρόνος εκτέλεσης είναι πιο αργός. Αναμένεται βελτίωση στο χρόνο εκτέλεσης και πιθανά και στο accuracy στο 3ο παραδοτέο(αν και ήδη έχει total_recall>0.91).
Η λογική των συναρτήσεων έχει μείνει ακριβώς ίδια με του πρώτου παραδοτέου,πέρα από κάποιες μικρές βελτιώσεις στη graph_creation συνάρτηση(βρίσκεται εσωτερικά της Vamana.cpp).

Και για filteredVamana αλλά και για stitched εχει υλοποιήθει και η εύρεση recall για unfiltered queries. Στο  FilteredVamana χρειάστηκε η υλοποίηση της λύσης που περιγράφηκε στο piazza (αντί για medoids βρίσκουμε το πιο κοντινό σημείο για κάθε medoid και περνάμε αυτά τα σημεία ως starting_points). Για το StitchedVamana δεν χρειάστηκαν κάποια ιδιαίτερη μεταχείριση τα ufniltered_queries.


Ενδεικτικές εκτελέσεις:

{
    "source_path": "dummy-data.bin",
    "query_path": "dummy-queries.bin",
    "num_data_dimensions": 102,
    "num_query_dimensions_offset": 2,
    "sample_proportion": 0.001,
    "alpha": 1.2,
    "R": 14,
    "knn": 100,
    "L_sizelist": 140,
    "Rsmall": 40,
    "Lsmall": 100,
    "Rstitched": 20


THE TOTAL RECALL FOR Filtered IS: 0.924605
The recall for filtered queries is:0.873217The recall for unfiltered queries in filteredVamana is0.975579

THE TOTAL RECALL FOR STITCHED IS0.890896
the recall for stitched unfiltered nodes is0.924618
the recall for stitched filtered node is0.856917
the elapsed time is 192.576
}



{
    "source_path": "dummy-data.bin",
    "query_path": "dummy-queries.bin",
    "num_data_dimensions": 102,
    "num_query_dimensions_offset": 2,
    "sample_proportion": 0.001,
    "alpha": 1.2,
    "R": 14,
    "knn": 100,
    "L_sizelist": 100,
    "Rsmall": 32,
    "Lsmall": 100,
    "Rstitched": 64

    THE TOTAL RECALL FOR Filtered IS: 0.924543
    The recall for filtered queries is:0.873362The recall for unfiltered queries in filteredVamana is0.975313

    THE TOTAL RECALL FOR STITCHED IS0.907309
    the recall for stitched unfiltered nodes is0.95096
    the recall for stitched filtered node is0.86331
    the elapsed time is 224.663
}

{
    "source_path": "dummy-data.bin",
    "query_path": "dummy-queries.bin",
    "num_data_dimensions": 102,
    "num_query_dimensions_offset": 2,
    "sample_proportion": 0.001,
    "alpha": 1.2,
    "R": 14,
    "knn": 100,
    "L_sizelist": 140,
    "Rsmall": 32,
    "Lsmall": 100,
    "Rstitched": 64

    THE TOTAL RECALL FOR Filtered IS: 0.924493
    The recall for filtered queries is:0.873314
    The recall for unfiltered queries in filteredVamana is0.975261

    THE TOTAL RECALL FOR STITCHED IS0.915027
    the recall for stitched unfiltered nodes is0.961742
    the recall for stitched filtered node is0.867934
    the elapsed time is 228.02
}




The euclidean caclulations take: 0.2464
 the queries size is5012
results written succesfully!
 The groundtuth took 0.239021
the elapsed time for graph creation is:0.325857
the elapsed time for graph creation is:1.24374
the elapsed time for graph creation is:0.0180715
the elapsed time for graph creation is:0.00875052
the elapsed time for graph creation is:0.00604243
the elapsed time for graph creation is:0.00922834
the elapsed time for graph creation is:0.0351788
the elapsed time for graph creation is:3.4931e-05
the elapsed time for graph creation is:0.00271763
the elapsed time for graph creation is:0.000182172
the elapsed time for graph creation is:1.996e-06
the elapsed time for graph creation is:0.00211753
the elapsed time for graph creation is:1.4775e-05
the elapsed time for graph creation is:0.000319977
the elapsed time for graph creation is:3.928e-06
the elapsed time for graph creation is:2.9413e-05
the elapsed time for graph creation is:0.000138412
the elapsed time for graph creation is:5.5753e-05
the elapsed time for graph creation is:1.968e-06
the elapsed time for graph creation is:1.7136e-05
the elapsed time for graph creation is:0.000642595
the elapsed time for graph creation is:1.4769e-05
the elapsed time for graph creation is:0.000690488
the elapsed time for graph creation is:5.957e-06
the elapsed time for graph creation is:9.0055e-05
the elapsed time for graph creation is:4.6186e-05
the elapsed time for graph creation is:6.2111e-05
the elapsed time for graph creation is:0.000997964
the elapsed time for graph creation is:4.622e-06
the elapsed time for graph creation is:0.000114778
the elapsed time for graph creation is:3.501e-06
the elapsed time for graph creation is:1.166e-06
the elapsed time for graph creation is:3.489e-05
the elapsed time for graph creation is:2.5652e-05
the elapsed time for graph creation is:0.000364524
the elapsed time for graph creation is:4.479e-06
the elapsed time for graph creation is:1.4713e-05
the elapsed time for graph creation is:6.06e-07
the elapsed time for graph creation is:4.48e-07
the elapsed time for graph creation is:4.5e-07
the elapsed time for graph creation is:6.095e-06
the elapsed time for graph creation is:7.2e-07
the elapsed time for graph creation is:4.89e-07
the elapsed time for graph creation is:5.43e-07
the elapsed time for graph creation is:1.4492e-05
the elapsed time for graph creation is:4.77e-07
the elapsed time for graph creation is:4.057e-06
the elapsed time for graph creation is:5.201e-06
the elapsed time for graph creation is:2.3073e-05
the elapsed time for graph creation is:9.02e-07
the elapsed time for graph creation is:2.104e-06
the elapsed time for graph creation is:4.29e-07
the elapsed time for graph creation is:1.4527e-05
the elapsed time for graph creation is:1.769e-06
the elapsed time for graph creation is:3.35e-06
the elapsed time for graph creation is:1.153e-06
the elapsed time for graph creation is:7.33e-07
the elapsed time for graph creation is:3.063e-06
the elapsed time for graph creation is:4.85e-07
the elapsed time for graph creation is:1.155e-06
the elapsed time for graph creation is:8.92e-07
the elapsed time for graph creation is:6.38e-07
the elapsed time for graph creation is:7.04e-07
the elapsed time for graph creation is:3.7095e-05
the elapsed time for graph creation is:2.03e-06
the elapsed time for graph creation is:9.36e-07
the elapsed time for graph creation is:4.52e-07
the elapsed time for graph creation is:1.438e-06
the elapsed time for graph creation is:9.2e-07
the elapsed time for graph creation is:5.75e-07
the elapsed time for graph creation is:5.375e-06
the elapsed time for graph creation is:2.504e-06
the elapsed time for graph creation is:1.061e-06
the elapsed time for graph creation is:7.02e-07
the elapsed time for graph creation is:9.55e-07
the elapsed time for graph creation is:4.3e-07
the elapsed time for graph creation is:4.54e-07
the elapsed time for graph creation is:6.35e-07
the elapsed time for graph creation is:7.38e-07
the elapsed time for graph creation is:3.753e-06
the elapsed time for graph creation is:2.177e-06
the elapsed time for graph creation is:4.8e-07
the elapsed time for graph creation is:4.78e-07
the elapsed time for graph creation is:6.14e-07
the elapsed time for graph creation is:1.06e-06
the elapsed time for graph creation is:1.831e-06
the elapsed time for graph creation is:6.41e-07
the elapsed time for graph creation is:3.853e-06
the elapsed time for graph creation is:5.05e-07
the elapsed time for graph creation is:5.43e-07
the elapsed time for graph creation is:9.73e-07
the elapsed time for graph creation is:1.405e-06
the elapsed time for graph creation is:4.93e-07
the elapsed time for graph creation is:5.32e-07
the elapsed time for graph creation is:6.55e-07
the elapsed time for graph creation is:9.2e-07
the elapsed time for graph creation is:5.17e-07
the elapsed time for graph creation is:6.74e-07
the elapsed time for graph creation is:4.66e-07
the elapsed time for graph creation is:4.53e-07
the elapsed time for graph creation is:6.65e-07
the elapsed time for graph creation is:4.68e-07
the elapsed time for graph creation is:6.46e-07
the elapsed time for graph creation is:4.92e-07
the elapsed time for graph creation is:6.55e-07
the elapsed time for graph creation is:1.646e-06
the elapsed time for graph creation is:5.44e-07
the elapsed time for graph creation is:4.88e-07
the elapsed time for graph creation is:5.11e-07
the elapsed time for graph creation is:7.21e-07
the elapsed time for graph creation is:6.88e-07
the elapsed time for graph creation is:4.48e-07
the elapsed time for graph creation is:5.59e-07
the elapsed time for graph creation is:6.42e-07
the elapsed time for graph creation is:4.58e-07
the elapsed time for graph creation is:5.17e-07
the elapsed time for graph creation is:6.39e-07
the elapsed time for graph creation is:6.02e-07
the elapsed time for graph creation is:4.71e-07
the elapsed time for graph creation is:5.68e-07
the elapsed time for graph creation is:6.28e-07
the elapsed time for graph creation is:1.401e-06
the elapsed time for graph creation is:5.28e-07
the elapsed time for graph creation is:4.87e-07
the elapsed time for graph creation is:6.5e-07
the elapsed time for graph creation is:6.15e-07
the elapsed time for graph creation is:6.53e-07
the elapsed time for graph creation is:6.23e-07
the elapsed time for graph creation is:4.91e-07