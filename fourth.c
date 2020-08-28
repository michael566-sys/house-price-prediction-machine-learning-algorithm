#include <stdlib.h>
#include <stdio.h>




//print 2D matrix 
int print2D ( double ** matrix, int row, int column ) {
    for ( int i = 0 ; i < row ; i ++ ) {

        for ( int j = 0 ; j < column ; j ++ ) {

            if ( j == column - 1 ) {
                printf ( "%lf\n" , matrix[i][j] );
            } else {
                printf ( "%lf\t" , matrix[i][j] ) ;
            }

        }

    }
    printf ("\n");

    return 0 ; 

}

// print 1D matrix
int print1D ( double * matrix, int row) {
     for ( int i = 0 ; i < row ; i ++ ) {
         
         printf( "%lf\t", matrix [i] );
       

    }
    printf( "\n");

    return 0 ; 

}

//print a row 
int printRow ( double*row, int length ) {
    printf( "row\n" ) ; 
    for ( int i = 0 ; i < length; i ++ ) {
        printf ( "%lf\t", row[i] ) ; 
    }
    printf ( "\n" ) ; 
    return 0 ; 
}


// transpose matrix 
double** tranpose ( double ** matrix, int row, int column ) {

    double ** transposeMatrix = (double **) malloc ( sizeof(double*)* column); 

    for ( int i = 0 ; i < column ; i ++ ) {

        transposeMatrix [i] = (double*) malloc ( sizeof( double ) * row ) ;  
    }

    for ( int i = 0 ; i < column; i ++ ) {

        for ( int j = 0 ; j < row; j ++ ) {

            transposeMatrix [i][j] = matrix[j][i];
            
        }

    }

    return transposeMatrix; 
}


//augmentation
double ** augmentation ( double**matrix, int row, int column ) { 

    double** augment = (double**) malloc ( sizeof(double*)* row);

    for ( int i = 0 ; i < row ; i ++ ) {
        
        augment[i]= (double* ) malloc ( sizeof ( double )* column*2 ) ; 

    }
    double one [row][column]; 

    for ( int i = 0 ; i < row ; i ++ ) {

        for ( int j = 0 ; j < column ; j ++ ) {

            if ( i == j ) {
                one[i][j] = (double) 1 ; 
            } else {
                one[i][j] = (double) 0 ; 
            }
        }

    }
    
    for ( int i = 0 ; i < row ; i ++ ) {
        for ( int j = 0 ; j < column *2 ; j ++ ) {

            if ( j < column ) {
                augment[i][j] = matrix [i][j];
            } else {
                augment [i][j] = one [i][j-column];
            }
        }
    }
    // printf("Augmented matrix: \n");
    // print2D ( augment,row, column*2 ); 

    return augment; 

}

//row subtraction operation 
double * rowSubtraction ( double * first, double * second, int rowLength, double multiple ) {
    
    for ( int i = 0 ; i < rowLength ; i ++ ) {

        first [i] = first[i] - (second [i] * multiple) ; 

    }
    // printf( "Row subtraction: \n");
    // printRow (first, rowLength ) ; 
    // printf("\n" ) ; 

    return first; 
}

//divide an entire row 
double * rowDivision ( double divident, double * row, int rowLength ) {

    for ( int i = 0 ; i < rowLength ; i ++ ) {

        row [i] = (row [i]) / divident; 

    }
    // printf( "Row division: \n");
    // printRow (row, rowLength ) ; 
    // printf("\n" ) ; 

    return row ;
}


//inverse of a matrix
double ** inverse ( double**aug, int row, int column ) {

    for ( int i = 0 ; i < row ; i ++ ) {

        int j = i ;

        if ( aug[j][i] != (double)1 ) {

            aug [j] = rowDivision (  aug[j][i] ,aug[j], column ) ;
        }
        int temp1 = j + 1; 
        while ( temp1 < row ) {
            if ( aug[temp1][i] != (double)0 ) {
                double multiple = aug[temp1][i] * aug [j][i];
                aug[temp1] = rowSubtraction ( aug[temp1] , aug[j], column, multiple ) ;          

            } 
            temp1 ++; 
        }
        int temp2 = j - 1; 
        while ( temp2 >= 0 ) {

            if ( aug[temp2] [i] != (double)0 ) {
                double multiple = aug[temp2][i] * aug [j][i];
                aug[temp2] = rowSubtraction ( aug [temp2] , aug[j], column, multiple) ;
            }
            temp2 -- ; 
        }
    }

    double ** matrix_inverse = (double**) malloc ( sizeof (double*) * row ); 

    for ( int i = 0 ; i < row; i ++ ) {
        matrix_inverse[i] = (double*) malloc ( sizeof (double) * row ) ; 
    }

    for ( int i = 0 ; i < row ; i ++ ) {

        for (int j = row ; j < column ; j ++ ) {

            matrix_inverse[i][j-row] = aug[i][j] ;

        }

    }

    return matrix_inverse; 

}



//multiply 2 matrices
double ** multiply ( double**m1, int m1_row, int m1_column, double**m2, int m2_row, int m2_column ){

    if (  m1_column != m2_row ) {
        printf( "m1_column != m2_row, matrices cannot multiply \n");
        return NULL; 
    }

    double** multi = (double**) malloc ( sizeof(double*)*( m1_row ));

    for ( int i = 0 ; i < m1_row ; i ++ ) {
        multi[i] = (double*) malloc ( sizeof (double) * m2_column );
    }

    for ( int i = 0 ; i < m1_row ; i ++ ) {

        for ( int j = 0; j < m2_column; j ++ ) {
            int k = 0 ; 
            int l = 0 ; 
            double temp = 0 ; 

            while ( ( k < m1_column ) && ( l < m2_row ) ) {
                temp = temp + m1[i][k] * m2[l][j] ; 
                // printf ( "temp (%lf) =  m1 (%lf) * m2 (%lf)\n", temp, m1[i][k], m2[l][j]);
                k ++ ; 
                l ++ ; 
            }
            multi [i][j] = temp;
        }

    }

    return multi; 

}





int main ( int argc, char*argv[] ) {

    if ( argc < 1 ) {
        printf ("No second argument\n");

    } else if ( argc < 2) {
        printf ("No third arguement\n");
    }

    char * trainingdata = argv[1]; 
    char * testingdata = argv[2]; 
    double one_double = (double) 1; 


// open training data file
    FILE * fp1 = fopen ( trainingdata, "r" ); 

    int k;
    int n;  

    fscanf ( fp1, "%d\n", &k) ; 

    fscanf ( fp1, "%d\n", &n) ; 

// matrix X is n by k+1 
    double ** matrix_X = (double**) malloc ( sizeof(double*)* n ) ;

    for ( int i = 0 ; i < n ; i ++ ) {

        matrix_X[i] = ( double* ) malloc ( sizeof ( double ) * (k+1) ) ;
        
    }

// matrix Y is n by 1
    double * matrix_Y = (double*) malloc ( sizeof(double) * n );
    int index_Y = 0; 

    
    for ( int i = 0 ; i < n ; i ++ ) {

        for ( int j = 0 ; j < k + 1 ; j ++ ) {

            if ( j == 0 ) {
                double temp; 
                fscanf ( fp1, "%lf," , &temp );
                
                matrix_X[i][j] = one_double;
                
                matrix_Y[index_Y] = temp; 
                index_Y ++; 
        
            } else if ( j == k ) {
                fscanf ( fp1, "%lf\n" , &matrix_X[i][j] );
            } else {
                fscanf ( fp1, "%lf," , &matrix_X[i][j] );
            }

        }

    }
    if (!feof(fp1)) {   
        printf ( "Haven't finish scanning! \n");
    }

    // printf ("array X is: \n") ;

    // print2D ( matrix_X, n , k + 1) ;

    // printf ("array Y is: \n");

    // print1D ( matrix_Y, n ) ; 


// close training data file
    fclose (fp1); 




// open testing data file 
    FILE * fp2 = fopen ( testingdata, "r"); 

    int m ; 

    fscanf ( fp2, "%d\n", &m );
    // printf ( "m is: %d\n", m );

    double ** matrix_Z = (double**) malloc ( sizeof(double*) * m );

    for ( int i = 0 ; i < m ; i ++ ) {
        matrix_Z [i] = (double*) malloc ( sizeof(double) * (k+1) ) ;
    }
    // printf ("value of k: %d\n" , k); 


    for ( int i = 0 ; i < m ; i ++ ) {

        for ( int j = 0 ; j < k+1 ; j ++ ) {

            if ( j == 0 ) {
                matrix_Z[i][j] = one_double;
            } else if ( j == k ) {
                fscanf ( fp2, "%lf\n", &matrix_Z[i][j] );
            } else {
                fscanf ( fp2, "%lf,", &matrix_Z[i][j] );
            }
        }

    }

    if (!feof(fp2)) {   
        printf ( "Haven't finish scanning! \n");
    }
    // printf( "matrix_Z is: \n");
    // print2D ( matrix_Z, m , k+1 );

// close testing data file 
    fclose (fp2);

// tranpose matrix X
    
    double ** transpose_X = tranpose ( matrix_X, n ,  k + 1 );

    // printf ("Transpose X is: \n");
    // print2D ( transpose_X , k + 1, n ) ; 

// multiply transpose X and X

    double ** transXMX = multiply (transpose_X, k+1, n, matrix_X, n, k+1 );
    
    // printf( "Multiply transpose X with X: \n");
    // print2D ( transXMX, k+1 , k+1 );
    
// augmenting transXMX
// augmented matrix is n by (k+1)*2
    double ** matrix_Aug = augmentation ( transXMX , k+1 , k+1 ); 

// inverse matrix_Aug     
    double ** matrix_Inverse = inverse ( matrix_Aug, k+1, 2*(k+1) ) ;

    // printf( "Inverse Matrix: \n");
    // print2D( matrix_Inverse , k+1, k+1 ) ;

// find weights

    double ** weights1;/* = (double**) malloc ( sizeof (double*) * (k+1) ) ;*/ 

    weights1 = multiply ( matrix_Inverse, k+1 , k+1, transpose_X, k+1, n ) ; 

    // printf( "Intermediate: \n");
    // print2D ( weights, k+1 ,n ) ; 


    double ** special_Y = (double**) malloc ( sizeof (double*) * (n) ) ; 
    
    for ( int i = 0 ; i < n; i ++ ) {

        special_Y[i] = (double*) malloc ( sizeof ( double* ) ); 
        special_Y[i][0] = matrix_Y[i] ; 

    }
    // printf ("Special_Y is: \n");
    // print2D( special_Y, n ,1 ) ; 
    double** weights2;
    weights2 = multiply ( weights1, k+1 , n , special_Y, n, 1);

    // printf( "Weights: \n");
    // print2D ( weights, k+1 ,1 ) ; 

// find price 
    double ** price; /* = (double**) malloc ( sizeof (double*) * (m) ) ; 
    
    for ( int i = 0 ; i < m; i ++ ) {

        price[i] = (double*) malloc ( sizeof ( double* ) ); 

    }*/

    price = multiply ( matrix_Z, m , k+1, weights2, k+1 ,1);

    // printf("Price is: \n");
    for ( int i = 0 ; i < m; i ++ ) {

        printf ( "%0.0lf\n", price[i][0]);

    }




// free X
    for ( int i = 0 ; i < n ; i ++ ){

        free( matrix_X[i] );
        matrix_X[i]=NULL;
        // matrix_X[i] contains ptr, so free this equals to free the ptr inside it
    }
    free(matrix_X);
    matrix_X=NULL;
// free tranpose X

    for ( int i = 0 ; i < k+1 ; i ++ ){

        free( transpose_X[i] );
        transpose_X[i]=NULL;

    }
    free (transpose_X);
    transpose_X=NULL;
// free transXMX
    for ( int i = 0 ; i < k+1 ; i ++ ){

        free( transXMX[i] );
        transXMX[i]=NULL;
    }
    free(transXMX);
    transXMX=NULL; 
// free Y
    free(matrix_Y); 
    matrix_Y = NULL; 
    
// free special_Y
    for ( int i = 0 ; i < n ; i ++ ){

        free( special_Y[i] );
        special_Y[i]=NULL;
    }
    free(special_Y); 
    special_Y=NULL;

// free Augmented Matrix 
    for ( int i = 0 ; i < k+1; i ++ ){

        free( matrix_Aug[i] );
        matrix_Aug[i]=NULL;
    }
    free(matrix_Aug);
    matrix_Aug=NULL;
// free matrix_Inverse 
    for ( int i = 0 ; i < k+1; i ++ ) {

        free(matrix_Inverse[i]);
        matrix_Inverse[i] = NULL;
    }
    free(matrix_Inverse);
    matrix_Inverse=NULL;

//free matrix_Z
   for (int i = 0 ; i< m; i ++){
	free (matrix_Z[i]);
	matrix_Z[i]=NULL;
   }
   free(matrix_Z);
   matrix_Z=NULL;

// free weights1
   for ( int i= 0; i < k +1; i ++ ){
	free (weights1[i]);
	weights1[i]=NULL;
   }
   free(weights1);
   weights1=NULL; 

// free weights2
   for ( int i= 0; i < k +1; i ++ ){
	free(weights2[i]);
	weights2[i]=NULL;
   }
   free(weights2);
   weights2=NULL;

// free price 
    for ( int i = 0 ; i < m; i ++ ) {

        free(price[i]);
        price[i] = NULL;
    }
    free(price);
    price = NULL;

    return 0 ; 


}
