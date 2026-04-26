#include <stdio.h>
#include <stdlib.h>

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    int i,j,k;
    float *** sector_times;
    scanf(" %u %u",n_drivers,n_laps);
    sector_times = (float ***)malloc(*n_drivers*sizeof(float**));
    for (i = 0; i<*n_drivers ; i++) {

        sector_times[i] = (float **) malloc(*n_laps*sizeof(float *));

        for (j = 0; j < *n_laps; j++) {

            sector_times[i][j] = (float *)malloc(3*sizeof(float));
        }

    }

    for (i=0;i < *n_drivers;i++){
        for (j=0;j < *n_laps;j++){
            for (k=0;k<3;k++){
                scanf("%f",&sector_times[i][j][k]);
            }
        }
    }


    return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    int i,j,k;
    unsigned int **positions;
    scanf("%u %u",p_drivers,n_races);
    positions=(unsigned int**)malloc(sizeof(unsigned int*)*(*p_drivers));

    for (k=0;k<*p_drivers;k++){
        positions[k]=(unsigned int*)malloc(sizeof(unsigned int)*(*n_races));
    }

    for (i=0;i<*p_drivers;i++){
        for (j=0;j<*n_races;j++){
            scanf(" %u",&positions[i][j]);
        }
    }
    return positions;
}

float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j,k;
    float sum=0;
    float** lap_times=(float**)malloc(sizeof(float*)*n_drivers);

    for (i=0;i<n_drivers;i++){
        lap_times[i]=(float*)malloc(sizeof(float)*n_laps);
    }

    for (i=0;i<n_drivers;i++){
        for (j=0;j<n_laps;j++){
            for (k=0;k<3;k++){
                sum=sum+sector_times[i][j][k];
                lap_times[i][j]=sum;
            }
            sum=0;
        }
    }

    return lap_times;
}
unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j;
    unsigned int driver;
    float fastest=lap_times[0][0];
    for (i=0;i<n_drivers;i++){
        for (j=0;j<n_laps;j++){
            if (fastest>lap_times[i][j]){
                fastest=lap_times[i][j];
                driver=i;
            }
        }
    }
    return driver;
}
unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    int i,j;
    unsigned int lap;
    float sum=0;
    float fastest;
    float *arr=(float*)malloc(sizeof(float)*n_laps);
    for(i=0;i<n_laps;i++){
        for(j=0;j<3;j++){
            sum=sum+sector_times_of_driver[i][j];
            arr[i]=sum;

        }
        sum=0;
    }
    fastest=arr[0];
    for(i=0;i<n_laps;i++){
        if (fastest>arr[i]){
            fastest=arr[i];
            lap=i;
        }
    }
    return lap;
}
float* selection_sort(float* arr, unsigned int len, char ord){
    int i,j;
    float t;
    float *sorted;
    sorted=arr;
    if (ord=='A'){
        for (i=0;i<len;i++){
            for (j=i;j<len;j++){
                if (sorted[i]>sorted[j]){
                    t=sorted[j];
                    sorted[j]=sorted[i];
                    sorted[i]=t;
                }
            }
        }
    }
    if (ord=='D'){
        for (i=0;i<len;i++){
            for (j=i;j<len;j++){
                if (sorted[i]<sorted[j]){
                    t=sorted[j];
                    sorted[j]=sorted[i];
                    sorted[i]=t;
                }
            }
        }
    }
    return sorted;
}
unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j;
    unsigned int temp;
    float t;
    float sum=0;
    float *arr=(float*)malloc(sizeof(float)*n_drivers);
    unsigned int *order=(unsigned int*)malloc(sizeof(unsigned int)*n_drivers);
    for(i=0;i<n_drivers;i++){
        for(j=0;j<n_laps;j++){
            sum=sum+lap_times[i][j];
            arr[i]=sum;

        }
        sum=0;
    }
    for (i=0;i<n_drivers;i++){
        order[i]=i;
    }
    for (i=0;i<n_drivers;i++){
        for (j=i+1;j<n_drivers;j++){
            if (arr[i]>arr[j]){
                t=arr[j];
                arr[j]=arr[i];
                arr[i]=t;
                temp=order[j];
                order[j]=order[i];
                order[i]=temp;
            }
        }
    }
    return order;

}
float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,unsigned int driver2){
    float *diff=(float*)malloc(sizeof(float)*n_laps);
    int i;
    for(i=0;i<n_laps;i++){
        diff[i]=lap_times[driver1][i]-lap_times[driver2][i];
    }

    for (i=1;i<n_laps;i++){
        diff[i]=diff[i]+diff[i-1];
    }


    return diff;
}
unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    int i,j,sum=0;
    unsigned int *points=(unsigned int*)malloc(sizeof(unsigned int)*p_drivers);
    unsigned int *total_points=(unsigned int*)malloc(sizeof(unsigned int)*p_drivers);
    for (i=0;i<p_drivers;i++){
        scanf("%u",&points[i]);
    }
    for (i=0;i<p_drivers;i++){
        for (j=0;j<n_races;j++){
            sum=sum+points[positions[i][j]-1];
            total_points[i]=sum;
        }
        sum=0;
    }
    return total_points;

}
unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    int i,j;
    unsigned int temp,t;
    unsigned int place;
    unsigned int *rank=(unsigned int*)malloc(sizeof(unsigned int)*p_drivers);
    for (i=0;i<p_drivers;i++){
        rank[i]=i;
    }
    for (i=0;i<p_drivers;i++){
        for (j=i+1;j<p_drivers;j++){
            if (total_points[i]<total_points[j]){
                t=total_points[j];
                total_points[j]=total_points[i];
                total_points[i]=t;
                temp=rank[j];
                rank[j]=rank[i];
                rank[i]=temp;
            }
        }
    }
    for (i=0;i<p_drivers;i++){
        if (rank[i]==id){
            place=i+1;
        }
    }
    return place;
}
