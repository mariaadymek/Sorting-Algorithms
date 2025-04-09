import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def create_images_directory():
    """Create images directory if it doesn't exist"""
    if not os.path.exists('images'):
        os.makedirs('images')
        print("Created 'images' directory")

def plot_reads_comparison():
    """Plot a comparison of reads for all sorting algorithms"""
    plt.figure(figsize=(12, 8))

    algorithms = ['bubble_sort', 'merge_sort', 'heap_sort', 'quick_sort']
    colors = ['blue', 'green', 'red', 'purple']

    for algo, color in zip(algorithms, colors):
        try:
            data = pd.read_csv(f'data/{algo}_reads.csv')
            plt.plot(data['size'], data['reads'], marker='o', linestyle='-', color=color, label=f'{algo.replace("_", " ").title()}')
        except Exception as e:
            print(f"Error reading data for {algo}: {e}")

    plt.title('Number of Reads by Algorithm and Input Size', fontsize=16)
    plt.xlabel('Input Size', fontsize=14)
    plt.ylabel('Number of Reads', fontsize=14)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()

    plt.savefig('images/reads_comparison.png', dpi=300, bbox_inches='tight')
    print("Saved reads comparison graph to images/reads_comparison.png")

    # Create a log scale version for better visibility of differences
    plt.yscale('log')
    plt.title('Number of Reads by Algorithm and Input Size (Log Scale)', fontsize=16)
    plt.savefig('images/reads_comparison_log.png', dpi=300, bbox_inches='tight')
    print("Saved log-scale reads comparison graph to images/reads_comparison_log.png")

    plt.close()

def plot_allocations_comparison():
    """Plot a comparison of allocations for all sorting algorithms"""
    plt.figure(figsize=(12, 8))

    algorithms = ['bubble_sort', 'merge_sort', 'heap_sort', 'quick_sort']
    colors = ['blue', 'green', 'red', 'purple']

    for algo, color in zip(algorithms, colors):
        try:
            data = pd.read_csv(f'data/{algo}_allocations.csv')
            plt.plot(data['size'], data['allocations'], marker='o', linestyle='-', color=color, label=f'{algo.replace("_", " ").title()}')
        except Exception as e:
            print(f"Error reading data for {algo}: {e}")

    plt.title('Memory Allocations by Algorithm and Input Size', fontsize=16)
    plt.xlabel('Input Size', fontsize=14)
    plt.ylabel('Number of Allocations (bytes)', fontsize=14)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()

    plt.savefig('images/allocations_comparison.png', dpi=300, bbox_inches='tight')
    print("Saved allocations comparison graph to images/allocations_comparison.png")

    # Create a log scale version for better visibility of differences
    plt.yscale('log')
    plt.title('Memory Allocations by Algorithm and Input Size (Log Scale)', fontsize=16)
    plt.savefig('images/allocations_comparison_log.png', dpi=300, bbox_inches='tight')
    print("Saved log-scale allocations comparison graph to images/allocations_comparison_log.png")

    plt.close()

def plot_individual_algorithms():
    """Create individual plots for each algorithm showing both reads and allocations"""
    algorithms = ['bubble_sort', 'merge_sort', 'heap_sort', 'quick_sort']

    for algo in algorithms:
        try:
            reads_data = pd.read_csv(f'data/{algo}_reads.csv')
            allocations_data = pd.read_csv(f'data/{algo}_allocations.csv')

            fig, ax1 = plt.subplots(figsize=(10, 6))

            # Plot reads on the left y-axis
            color = 'tab:blue'
            ax1.set_xlabel('Input Size', fontsize=12)
            ax1.set_ylabel('Number of Reads', color=color, fontsize=12)
            ax1.plot(reads_data['size'], reads_data['reads'], color=color, marker='o', linestyle='-')
            ax1.tick_params(axis='y', labelcolor=color)

            # Create a second y-axis for allocations
            ax2 = ax1.twinx()
            color = 'tab:red'
            ax2.set_ylabel('Memory Allocations (bytes)', color=color, fontsize=12)
            ax2.plot(allocations_data['size'], allocations_data['allocations'], color=color, marker='s', linestyle='-')
            ax2.tick_params(axis='y', labelcolor=color)

            algo_name = algo.replace('_', ' ').title()
            plt.title(f'{algo_name} Performance Metrics', fontsize=14)
            plt.grid(True, linestyle='--', alpha=0.3)

            fig.tight_layout()
            plt.savefig(f'images/{algo}_metrics.png', dpi=300, bbox_inches='tight')
            print(f"Saved {algo} metrics graph to images/{algo}_metrics.png")

            plt.close()

        except Exception as e:
            print(f"Error creating individual plot for {algo}: {e}")

def plot_stability_results():
    """Create a bar chart showing stability test results"""
    try:
        stability_data = pd.read_csv('data/stability_test.csv')

        plt.figure(figsize=(10, 6))

        algorithms = stability_data['algorithm'].tolist()
        is_stable = [1 if val == 'true' else 0 for val in stability_data['is_stable'].tolist()]

        # Create nice algorithm names
        algo_names = [algo.replace('_', ' ').title() for algo in algorithms]

        colors = ['green' if stable else 'red' for stable in is_stable]

        plt.bar(algo_names, is_stable, color=colors)
        plt.yticks([0, 1], ['Unstable', 'Stable'])
        plt.title('Stability of Sorting Algorithms', fontsize=16)
        plt.xlabel('Algorithm', fontsize=14)
        plt.ylabel('Stability', fontsize=14)

        for i, val in enumerate(is_stable):
            label = "Stable" if val == 1 else "Unstable"
            plt.text(i, 0.5, label, ha='center', va='center', color='white', fontweight='bold')

        plt.tight_layout()
        plt.savefig('images/stability_results.png', dpi=300, bbox_inches='tight')
        print("Saved stability results graph to images/stability_results.png")

        plt.close()

    except Exception as e:
        print(f"Error creating stability plot: {e}")

def plot_theoretical_complexity():
    """Create a plot showing theoretical time complexity of different sorting algorithms"""
    plt.figure(figsize=(12, 8))

    # Define input sizes and theoretical complexities
    n = np.arange(10, 1001, 10)

    # Best case complexities
    plt.plot(n, n, label='O(n) - Best case for Bubble Sort', color='lightblue', linestyle='--')
    plt.plot(n, n * np.log2(n), label='O(n log n) - Best/Average/Worst case for Merge Sort', color='green')
    plt.plot(n, n * np.log2(n), label='O(n log n) - Best/Average/Worst case for Heap Sort', color='red')
    plt.plot(n, n * np.log2(n), label='O(n log n) - Best/Average case for Quick Sort', color='purple')

    # Worst case complexities
    plt.plot(n, n**2, label='O(n²) - Average/Worst case for Bubble Sort', color='blue')
    plt.plot(n, n**2, label='O(n²) - Worst case for Quick Sort', color='darkviolet', linestyle=':')

    plt.title('Theoretical Time Complexity of Sorting Algorithms', fontsize=16)
    plt.xlabel('Input Size (n)', fontsize=14)
    plt.ylabel('Operations', fontsize=14)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(loc='upper left')

    plt.savefig('images/theoretical_complexity.png', dpi=300, bbox_inches='tight')
    print("Saved theoretical complexity graph to images/theoretical_complexity.png")

    # Log scale version
    plt.yscale('log')
    plt.title('Theoretical Time Complexity of Sorting Algorithms (Log Scale)', fontsize=16)
    plt.savefig('images/theoretical_complexity_log.png', dpi=300, bbox_inches='tight')
    print("Saved log-scale theoretical complexity graph to images/theoretical_complexity_log.png")

    plt.close()

def generate_markdown_content():
    """Generate markdown content for README.md with embedded images"""
    markdown = """# Sorting Algorithms Analysis

## Project Overview
This project implements and analyzes several common sorting algorithms:
- Bubble Sort
- Merge Sort
- Heap Sort
- Quick Sort

The analysis focuses on two main performance metrics:
1. **Number of Reads**: How many times the algorithm reads from memory
2. **Memory Allocations**: How much memory (in bytes) the algorithm allocates

Additionally, we test each algorithm for stability (whether elements with equal keys maintain their original order).

## Performance Analysis

### Reads Comparison
![Reads Comparison](images/reads_comparison.png)

For better visibility of differences between algorithms, here's the same data on a logarithmic scale:
![Reads Comparison (Log Scale)](images/reads_comparison_log.png)

### Memory Allocations Comparison
![Allocations Comparison](images/allocations_comparison.png)

For better visibility of differences between algorithms, here's the same data on a logarithmic scale:
![Allocations Comparison (Log Scale)](images/allocations_comparison_log.png)

## Individual Algorithm Performance

### Bubble Sort
![Bubble Sort Performance](images/bubble_sort_metrics.png)

### Merge Sort
![Merge Sort Performance](images/merge_sort_metrics.png)

### Heap Sort
![Heap Sort Performance](images/heap_sort_metrics.png)

### Quick Sort
![Quick Sort Performance](images/quick_sort_metrics.png)

## Stability Analysis
![Stability Results](images/stability_results.png)

## Theoretical Time Complexity
![Theoretical Time Complexity](images/theoretical_complexity.png)

For better visibility of asymptotic behavior, here's the same data on a logarithmic scale:
![Theoretical Time Complexity (Log Scale)](images/theoretical_complexity_log.png)

## Conclusion
Based on the analysis:

1. **Bubble Sort** has the highest number of reads and generally performs worst on large inputs, which matches its O(n²) average time complexity.
2. **Merge Sort** uses more memory allocations but performs consistently with its O(n log n) time complexity.
3. **Heap Sort** provides O(n log n) performance with less memory usage than Merge Sort.
4. **Quick Sort** shows good average-case performance but may degrade to O(n²) in worst-case scenarios.
5. **Bubble Sort** and **Merge Sort** maintain stability, while **Heap Sort** and **Quick Sort** do not (in their standard implementations).

This analysis demonstrates the trade-offs between time efficiency, memory usage, and stability when choosing a sorting algorithm.
"""

    with open('README.md', 'w') as f:
        f.write(markdown)

    print("Generated README.md with embedded graphs")

def main():
    print("Starting graph generation...")

    # Create images directory
    create_images_directory()

    # Create all the plots
    plot_reads_comparison()
    plot_allocations_comparison()
    plot_individual_algorithms()
    plot_stability_results()
    plot_theoretical_complexity()

    # Generate README.md with embedded images
    generate_markdown_content()

    print("Graph generation complete!")

if __name__ == "__main__":
    main()