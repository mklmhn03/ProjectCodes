# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from asyncio import base_tasks
from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and child states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        TODO: Design a better evaluation function here. (part 2a)

        The evaluation function takes in the current and proposed child
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        childGameState = currentGameState.getPacmanNextState(action)
        newPos = childGameState.getPacmanPosition()
        newFood = childGameState.getFood()
        newGhostStates = childGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        fod = newFood.asList()#+childGameState.getCapsules()
        if len(newFood.asList()) == currentGameState.getNumFood():#+len(currentGameState.getCapsules()):
            num = 100000
            for ball in newFood.asList():
                if manhattanDistance(ball, newPos) < num:
                    num = manhattanDistance(ball, newPos)
                    break
        # for capsule in childGameState.getCapsules():
        #     if ball == capsule and manhattanDistance(ball, newPos) < num+10:
        #         num = manhattanDistance(ball, newPos)+10
        #         break
                
        else:
            num = 0
        for ghost in newGhostStates:
            if (ghost.scaredTimer>0 and manhattanDistance(ghost.getPosition(), newPos) < num+5):
                num = manhattanDistance(ghost.getPosition(), newPos)+5
            else:
                if manhattanDistance(ghost.getPosition(), newPos) <1:
                    num+=100000
                elif manhattanDistance(ghost.getPosition(), newPos) <2:
                    num+=90000
        return -num

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent and AlphaBetaPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    TODO: Your minimax agent (part 2b)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.getNextState(agentIndex, action):
        Returns the child game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        # front = []
        # ghostfront = []
        # front.append((problem.startState, []))

        # bestscore = -float("inf")
        # for ghost in range (1, gameState.getNumAgents()):
        #     for ghostAct in gameState.getLegalActions(ghost):
        #         if gameState.getNextState(ghost, ghostAct)
        #         ghostfront.append(gameState.getNextState(ghost, ghostAct), acts+[ghostAct])
        #     front.append(ghostfront)
        # for ghostnodes in ghostfront:

        if gameState.isWin() or gameState.isLose():
            return Directions.STOP

        bestval = -100000
        bestmove = Directions.STOP
        for act in gameState.getLegalActions(0):
            nextState = gameState.getNextState(0, act)

            val = self.minimax(nextState, 1)
            if val > bestval:
                bestval = val
                bestmove = act
        return bestmove
    
    def minimax(self, gameState, depth):
        agent = depth%gameState.getNumAgents()
        if gameState.isWin() or gameState.isLose() or self.depth == depth//gameState.getNumAgents():
            return self.evaluationFunction(gameState)

        ghostpac = []
        for act in gameState.getLegalActions(agent):
            ghostpac.append(self.minimax(gameState.getNextState(agent, act), depth+1))

        if agent == 0:
            return max(ghostpac)
        else:
            return min(ghostpac)
            
        # else:
        #     for ghost in range (1, gameState.getNumAgents()):
        #         for act in gameState.getLegalActions(ghost):
        #             ghostpac.append(self.minimax(gameState.getNextState(ghost, act), depth+1))
        #     score = min(ghostpac)


class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    TODO: Your minimax agent with alpha-beta pruning (part 2c)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        if gameState.isWin() or gameState.isLose():
            return Directions.STOP

        bestval = -float("inf")
        bestmove = Directions.STOP
        alpha = bestval
        for act in gameState.getLegalActions(0):
            nextState = gameState.getNextState(0, act)

            val = self.minimax(nextState, 1, alpha, float("inf"))
            if val > bestval:
                bestval = val
                bestmove = act
                alpha = bestval
        return bestmove

    def minimax(self, gameState, depth, alpha, beta):
        agent = depth%gameState.getNumAgents()
        if gameState.isWin() or gameState.isLose() or self.depth == depth//gameState.getNumAgents():
            return self.evaluationFunction(gameState)

        if agent == 0:
            bestval = -float("inf")
            for act in gameState.getLegalActions(agent):
                bestval = max(bestval, self.minimax(gameState.getNextState(agent, act), depth+1, alpha, beta))

                if bestval >= beta:
                    return bestval
                alpha = max(bestval, alpha)
            return bestval
        else:
            bestval = float("inf")
            for act in gameState.getLegalActions(agent):
                bestval = min(bestval, self.minimax(gameState.getNextState(agent, act), depth+1, alpha, beta))
                
                if bestval <= alpha:
                    return bestval
                beta = min(bestval, beta)
            return bestval