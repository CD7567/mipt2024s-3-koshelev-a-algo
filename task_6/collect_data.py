import subprocess
import sys
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


# Setup base data directory
BASE_DIR = f'{sys.path[0]}'
RUNNER = f'{sys.path[0]}/../cmake-build-release/task_6/profiler/profiler'


# Run cmake compilation
subprocess.run(
    [
        'cmake',
        '-DCMAKE_BUILD_TYPE=Release',
        '-GNinja',
        '-B',
        f'{sys.path[0]}/../cmake-build-release',
        f'{sys.path[0]}/../'
    ]
)
subprocess.run(
    [
        'cmake',
        '--build',
        f'{sys.path[0]}/../cmake-build-release'
    ]
)


# Clear data files if exist
subprocess.run(
    [
        'rm',
        f'{BASE_DIR}/data/data.csv',
    ]
)


# Register data collection runners
subprocess.run(
    [
        f'{RUNNER}',
        f'{BASE_DIR}/data/data.csv',
        sys.argv[1],
        sys.argv[2],
        sys.argv[3]
    ]
)


# Read collected data from csv
df = pd.read_csv(f'{BASE_DIR}/data/data.csv', sep=',', skipinitialspace=True)
df_grouped = df.groupby(['TAG', 'METHOD', 'SIZE'], as_index=False).median(numeric_only=True)


# Pyplot params
plt.ioff()
plt.rcParams['text.usetex'] = True


# Plots constructor
def create_graph(
        tags: list[str],
        method: str,
        title: str,
        legend: list[str],
        savefile: str
):
    dfs = [
        df_grouped[
            np.logical_and(
                df_grouped['TAG'] == f'{tag}',
                df_grouped['METHOD'] == method
            )
        ]
        for tag in tags
    ]

    colors = [
        'orange',
        'blue',
        'green'
    ]

    fig = plt.figure()
    plt.grid()
    plt.title(title)
    plt.xlabel(r'$\mathrm{size}$')
    plt.ylabel(r'$\mathrm{time},\ \mathrm{ms}$')

    for frame, color in zip(dfs, colors):
        plt.plot(frame['SIZE'], frame['DURATION'], color=color, alpha=0.5)

    plt.legend(legend)

    plt.savefig(savefile, format='png', dpi=300)
    plt.close(fig)


# Create graphs for article
create_graph(
    ['HASH', 'AVL', 'ARRAY'],
    'ADD',
    'Comparison of ADD performance',
    [
        r'CHash',
        r'CAVLTree',
        r'new T*'
    ],
    f'{BASE_DIR}/data/add_cmp.png'
)

create_graph(
    ['HASH', 'AVL', 'ARRAY'],
    'FIND',
    'Comparison of FIND performance',
    [
        r'CHash',
        r'CAVLTree',
        r'new T*'
    ],
    f'{BASE_DIR}/data/find_cmp.png'
)

create_graph(
    ['HASH', 'AVL', 'ARRAY'],
    'FIND2N',
    'Comparison of FIND non-existent performance',
    [
        r'CHash',
        r'CAVLTree',
        r'new T*'
    ],
    f'{BASE_DIR}/data/find2n_cmp.png'
)

create_graph(
    ['HASH', 'AVL', 'ARRAY'],
    'CLEAR',
    'Comparison of CLEAR performance',
    [
        r'CHash',
        r'CAVLTree',
        r'new T*'
    ],
    f'{BASE_DIR}/data/clear_cmp.png'
)

create_graph(
    ['HASH', 'AVL'],
    'REMOVE',
    'Comparison of REMOVE non-existent performance',
    [
        r'CHash',
        r'CAVLTree'
    ],
    f'{BASE_DIR}/data/remove_cmp.png'
)
