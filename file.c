// Polynomial Multiplier

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int index, coefficient;
    struct node * next_node;  
} node;

node * create_node(int index, int coefficient)
{
    node * new_node = (node *) malloc(sizeof (node));
    
    new_node -> index = index;
    new_node -> coefficient = coefficient;
    
    new_node -> next_node = NULL;
    
    return new_node;
}

node * add_node(node * first_node, int index, int coefficient)
{
    node * new_node = create_node(index, coefficient);
    
    if (first_node == NULL)
        return new_node;
    
    node * node_pointer = first_node;
    
    while (node_pointer -> next_node != NULL)
        node_pointer = node_pointer -> next_node;
    
    node_pointer -> next_node = new_node;
    
    return first_node;
}

node * copy_list(node * head_node)
{
    if (head_node == NULL) return NULL;
    
    node * new_node = (node *) malloc(sizeof (node));
    
    new_node -> index = head_node -> index;
    new_node -> coefficient = head_node -> coefficient;
    
    new_node -> next_node = copy_list(head_node -> next_node);
    
    return new_node;
}

void print_list(node * node)
{
    while (node -> next_node != NULL)
    {
        if (node -> coefficient > 1)
            printf("%d", node -> coefficient);
            
        if ((node -> index) > 0)
            printf("x");
            
        if (node -> index > 1)
            printf("^%d", node -> index);
        
        if (node -> next_node != NULL && node -> next_node -> coefficient > 0)
            printf(" + ");
            
        node = node -> next_node;
    }
    
    if (node -> coefficient > 0)
        printf("%d", node -> coefficient);
            
    if ((node -> index) > 0)
        printf("x");
            
    if (node -> index > 1)
        printf("^%d", node -> index);
}

void simplify_polynomial(node * first_node)
{
    node * comparator_monomial = NULL;
    node * compared_monomial = NULL;
    node * matched_monomial = NULL;
    
    comparator_monomial = first_node;
    
    while (comparator_monomial != NULL && comparator_monomial -> next_node != NULL)
    {
        compared_monomial = comparator_monomial;

        while (compared_monomial -> next_node != NULL)
        {
            if (comparator_monomial -> index == compared_monomial -> next_node -> index)
            {
                comparator_monomial -> coefficient += compared_monomial -> next_node -> coefficient;
                matched_monomial = compared_monomial -> next_node;
                compared_monomial -> next_node = compared_monomial -> next_node -> next_node;
                
                free(matched_monomial);
            }
            else compared_monomial = compared_monomial -> next_node;
        }
        
        comparator_monomial = comparator_monomial -> next_node;
    }
}

node * multiply_two_polynomials(node * first_polynomial, node * second_polynomial, node * product_polynomial, int simplify)
{
    node * first_polynomial_node = first_polynomial;
    node * second_polynomial_node = second_polynomial;
    
    while (first_polynomial_node != NULL)
    {
        while (second_polynomial_node != NULL)
        {
            int index, coefficient;
            
            index = first_polynomial_node -> index + second_polynomial_node -> index;
            coefficient = first_polynomial_node -> coefficient * second_polynomial_node -> coefficient;
            
            product_polynomial = add_node(product_polynomial, index, coefficient);
            
            second_polynomial_node = second_polynomial_node -> next_node;
        }
        
        second_polynomial_node = second_polynomial;
        first_polynomial_node = first_polynomial_node -> next_node;
    }
    
    if (simplify) simplify_polynomial(product_polynomial);
    
    return product_polynomial;
}

node * exponentiate_polynomial(node * polynomial, int index)
{
    node ** dynamic_array = (node **) malloc((index + 1) * sizeof (node));
    
    dynamic_array[0] = polynomial;
        
    for (int i = 1; i < index; i++)
    {
        dynamic_array[i] = multiply_two_polynomials(polynomial, dynamic_array[i - 1], dynamic_array[i], 1);
      
        // printf("\n");
        // print_list(dynamic_array[i]);
        // printf("\n");
    }
    
    return dynamic_array[index - 1];
}

int main()
{
    // node * first_polynomial = NULL;
    // node * second_polynomial = NULL;
    // node * product_polynomial = NULL;
    // node * simplified_polynomial = NULL;
    
    // first_polynomial = create_node(1, 1);
    // first_polynomial = add_node(first_polynomial, 0, 1);
    
    // second_polynomial = create_node(1, 1);
    // second_polynomial = add_node(second_polynomial, 0, 1);
    
    // printf("First polynomial: ");
    // print_list(first_polynomial);
    
    // printf("\n");
    
    // printf("Second polynomial: ");
    // print_list(second_polynomial);
    
    // product_polynomial = multiply_two_polynomials(first_polynomial, second_polynomial, product_polynomial, 1);
    
    // printf("\n\n");
    
    // printf("(");
    // print_list(first_polynomial);
    // printf(") * (");
    // print_list(second_polynomial);
    // printf(") æ ");
    // print_list(product_polynomial);
    
    node * binomial = NULL;
    binomial = create_node(1, 1);
    binomial = add_node(binomial, 0, 1);
    
    // printf("\n\n");
    
    int exponent = 1;
    
    for (;;)
    {    
        printf("Enter an integer power of the binomial (x + 1): ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, temp;

      	status = scanf("%d", &input);
      	
      	while (status != 1)
      	{
              while ((temp = getchar()) != EOF && temp != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter an integer power of the binomial (x + 1): ");
              
              status = scanf("%d", &input);
      	}
      
      	exponent = input;
      	
      	node * raised_polynomial = exponentiate_polynomial(binomial, exponent);
      	
      	printf("\n");
      	printf("(x + 1)^%d æ ", exponent);
      	print_list(raised_polynomial);
      	printf("\n");

        printf("\n");
    }
    
    return 0;
}
