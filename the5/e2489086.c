#include <stdio.h>
#include <stdlib.h>
#include "the3.h"

int cs(char fir[], char sec[])
{
    int i = 0;

    while (fir[i] == sec[i]) {
        if (fir[i] == '\0' || sec[i] == '\0')
            break;
        i++;
    }

    if (fir[i] == '\0' && sec[i] == '\0')
        return 0;
    else
        return -1;
}

Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth){
    int i;
    Apartment *current;
    Apartment *newnode;
    newnode=malloc(sizeof(Apartment));
    newnode->name=apartment_name;
    newnode->max_bandwidth=max_bandwidth;
    newnode->flat_list=NULL;
    if (head==NULL){
        newnode->next=newnode;
        head=newnode;
    }
    if (index==0){
        newnode->next=head;
        current=head;
        while (current->next!=head){
            current=current->next;
        }
        current->next=newnode;
        head=newnode;
    }
    else{
        current=head;
        for (i=2;i<=index;i++){
            current=current->next;
        }
        newnode->next=current->next;
        current->next=newnode;
    }
    return head;
}
void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth){
    int i,sum;
    Flat *newflat,*lst,*temp,*t,*te;
    Apartment *current;
    current=head;
    newflat=malloc(sizeof(Flat));
    do {
        if (cs(current->name,apartment_name)==0){
            break;
        }
        current=current->next;
    } while (current!=head);
    lst=current->flat_list;
    newflat->id=flat_id;
    newflat->is_empty=0;
    sum=0;
    t=lst;
    if (t==NULL){
        newflat->next=NULL;
        newflat->prev=NULL;
        lst=newflat;
    }
    while (t!=NULL){
        sum=sum+t->initial_bandwidth;
        t=t->next;
    }
    if (sum+initial_bandwidth<current->max_bandwidth){
        newflat->initial_bandwidth=initial_bandwidth;
    }
    else {
        newflat->initial_bandwidth=current->max_bandwidth-sum;
    }
    if (index==0){
        te=lst;
        newflat->next = te;
        newflat->prev = NULL;
        te->prev=newflat;
        te=newflat;
    }
    else {
        temp=lst;
        i=1;
        while (i<index && temp!=NULL){
            temp=temp->next;
            i++;
        }
        if (temp!=NULL){
            newflat->next = temp->next;
            newflat->prev = temp;
            if (temp->next!=NULL){
                temp->next->prev=newflat;
            }
            temp->next=newflat;
        }

    }
}
Apartment* remove_apartment(Apartment* head, char *apartment_name){
    Apartment *curr,*pre;
    Flat *f,*tem;
    curr=head;

    if (cs(curr->name,apartment_name)==0){
        curr=head;
    }
    else {
        while(cs(curr->name,apartment_name)==-1){
            pre=curr;
            curr=curr->next;
        }
    }
    f=curr->flat_list;
    while (f!=NULL){
        tem=f->next;
        free(f);
        f=tem;
    }
    if (curr->next == head){
        head = NULL;
        free(curr);

    }
    else if (curr == head){
        pre = head;
        while (pre->next != head) pre = pre->next;
        head = curr->next;
        pre->next = head;
        free(curr);
    }
    else if (curr->next == head && curr == head)
    {
        pre->next = head;
        free(curr);
    }
    else
    {
        pre->next = curr->next;
    }

    return head;
}
void make_flat_empty(Apartment* head, char* apartment_name, int flat_id){
    Apartment *cur;
    Flat *h;
    cur=head;
    do {
        if (cs(cur->name,apartment_name)==0){
            break;
        }
        cur=cur->next;
    } while (cur!=head);
    h=cur->flat_list;
    while (h!=NULL){
        if (h->id==flat_id){
            break;
        }
        h=h->next;
    }
    h->is_empty=1;
    h->initial_bandwidth=0;
}
int find_sum_of_max_bandwidths(Apartment* head){
    Apartment *c;
    int num;
    num=0;
    if (head==NULL){
        return 0;
    }
    c=head;
    do {
        num=num+c->max_bandwidth;
        c=c->next;
    } while (c!=head);
    return num;
}
Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2){
    Flat *h2;
    Apartment *curr,*cur;
    curr=head;
    do {
        if (cs(curr->name,apartment_name_1)==0){
            break;
        }
        curr=curr->next;
    } while (curr!=head);
    cur=head;
    do {
        if (cs(cur->name,apartment_name_2)==0){
            break;
        }
        cur=cur->next;
    } while (cur!=head);
    h2=cur->flat_list;
    curr->max_bandwidth=curr->max_bandwidth+cur->max_bandwidth;
    if (h2==NULL){
        remove_apartment(head, cur->name);
    }
    return head;
}

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list){

}

