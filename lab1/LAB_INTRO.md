# Lab01-Intro
Through the whole semester, we will use github to hand out homework assignments and lab examples. We recommend to use c9 for coding. 

Basic commands to keep in mind:
#### git clone
Git clone is used to download a remote source code base(termed repository). To download a repository (assignment in our case), go to the github page, and find the 'Clone or Download' button, click it, copy the URL that ends with '.git', and run the following command in your workspace's terminal.
```
> git clone YOUR_URL_COPIED
```

#### git pull
Suppose the origin repository you downloaded before has changed, and you want to stay up-to-date with the remote repository, you can use the following command:
```
> git pull origin master
```


#### To submit your homework
Simply download your folder (**NOTE: not the whole workspace**) for current assignment. Download the folder as a .tar.gz file (c9 default), and name the file as FirstnameLastname_LabNUMBER. For example, your name is Bob Dylan, you are submitting homework assignment for lab02, download your folder containing all the files for lab02 as .tar.gz file and rename it as *BobDylan_Lab02.tar.gz*, then send to your TA.

There are a lot other useful (especially for verion control and teamwork) git commands, such as git commit, git checkout, git merge, git push, if you're interested, please refer to the following link for details:

[Git cheat sheet] (https://services.github.com/kit/downloads/github-git-cheat-sheet.pdf)

Also, the following URL links to a concrete project example: 

[A concreate project example] (https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging)
