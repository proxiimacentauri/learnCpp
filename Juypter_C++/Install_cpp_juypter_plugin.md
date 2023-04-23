#####################################################
###########     Installing xeus-cling     ###########
#####################################################

conda info --envs
conda create -n cling
conda info --envs
source activate cling
conda list

conda install xeus-cling -c conda-forge
conda remove libcxx --force
conda install jupyterlab -c conda-forge
jupyter-notebook