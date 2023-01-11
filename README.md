# GeneticZombieGame



## Research Notes

Reinforcement learning works on the usage of rewards (Postive and Negative) to learn how to behave in its environment. Do something good (stay alive / pick up coin) will reward the agent with positive points, while taking damage will give a negative reward.  
The goal of the agent is to maximize the cumulative reward.


For the Zombie game, i want to try Implementing Deep Reinforcement Learning using Q-learning.
The RL process is also called the Markov Decision Process (MDP)
The markov property implies that we do not need to know the history of all the states and actions to decide what to do / what action, only the current state.


### Observations / States space
Description of the world, what the environment currently looks like. With NO hidden information.
For the zombiegame we dont get the environments, but we can make observations. Which is a partial description of the environment / state.

The word state however gets used interchangeably for observations and states.


### Action Space
The action space defines the set of all posible actions the agent can take in an environment, these actions can come fro both a discrete or a continuous space:
In a discrete space, the number of actions the agent can take is finite. Meaning theres a fixed amount of actions you can take. For example in the game Tic Tac Toe, you can only perform 9 actions (place a cross in either of the 9 slots)
In the examples i found, they used mario to define a finite space, but i dont think that is fully fair, since you can adjust how you jump by adjusting it with the arrow keys (and land on a platform).  
 
  In continious space, the possible number of actions is infinite. For example driving a car: what steering angle to take (can be 20.1, 20.2, 20.15, ...).
  
 This information is crucial in the decision what RL algorithm to use.
 
 ### Rewards and discounting
 Rewards are crucial for the Reinforcement Learning, since its the only way the agent can learn about the environment.  
 
 The cumulative reward is the total of all rewards received at every timestep / the whole sequence)
 
 
 Discounting the reward is the act of multiplying the reward with a gamma value (that ranges from 0 - 1, and usually between 0.99 and 0.95).
 This gamma value gets powered to the value of the current timestep to cause future rewards to be less and less rewarding the further in the future it is. (we do this because it is less and less likely to happen).
 
 The cumulative reward can then be described using this formula (credit to huggingface.co)
![Image](https://huggingface.co/datasets/huggingface-deep-rl-course/course-images/resolve/main/en/unit1/rewards_4.jpg "Cumulative Reward")

### Tasks
A task is an instance of an RL problem. Theres 2 types. episodic and continuing.

An **episodic** task means theres a start point and an end point, resulting in an **Episode**
which is in essence a list of states, actions, rewards and new states.
An episode could for example be, the start of a game until you are killed or reached the end of a level.

**Continious** tasks are tasks that continue forever (du). 
They are tasks that have no termination state (like death, end of level, etc.)
Example could be automated stock trading, the agent keeps running until we decide to stop it.  



### Exploration vs Exploitation
Exploration is trying to do random actions in order to find more information about the environment (exploring the environment)

Exploitation is exploiting the known information to maximize reward.

The agent will need to balance between the 2 to maximize reward.
-> Exploiting current information too much will cause the agent to miss out on important information. In the zombie game this can for example be finding new villages.  

-> Exploring allows the agent then to find new information that it can use to maximize the reward.



### The agent's brain: Policy π

The policy π is the brain of our agent. it will tell us what action to take for the given state.  
We can also call it the agents behavior.  
Our goal is to optimize this policy for maximal cumulative reward.  

There are 2 approaches to this.  
* Directly: Teaching the agent what action to take given the current state.  -> Policy-Based methods
* Indirectly: Teach the agent what state is more valuable, then take action that leads to more valuable states -> Value-Based methods.

#### Policy based
In policy based methods we learn a policy function directly.  
This will generate a mapping between every state and its best corresponding action.  
-> Basically saying for each given state what action to take, or what action has the highest probability

2 types of policies:
* Deterministic: A policy at a given state will always return the same action.
* Stochastic: Outputs a probability distribution over different actions.

#### Value based  
For value based methods we train a value function, that maps a state to the expected value of being at that state.

The value of a state is the expected discounted reward the agent can get if it starts in that state.
The agent will then always act so that it ends up in a more rewarding state. 


### Deep RL
The deep in Deep reinforcement learning comes from the introduction of deep neural networks to solve Reinforcement Learning problems.

There are 2 value-based algorithms, Q-learning and Deep Q-learning. 
With Q learning, we use a traditional algorithm to create a Q table that helps us find what action to take for each state.  
  
With Deep Q learning. a neural network is used to approximate the q value



## Requirements

* Cuda: https://developer.nvidia.com/cuda-downloads
* cuDNN: https://developer.nvidia.com/rdp/cudnn-download  
	- https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html#install-windows
* Zlib: http://www.winimage.com/zLibDll/zlib123dllx64.zip
* Pytorch: https://pytorch.org/cppdocs/installing.html
* NVTX: https://docs.nvidia.com/nvtx/index.html


### Sources:
* https://huggingface.co/deep-rl-course
* https://pytorch.org/tutorials/advanced/cpp_extension.html