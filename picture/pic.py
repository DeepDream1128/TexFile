from graphviz import Digraph

dot = Digraph(comment='Code Structure', format='jpg')

# Add nodes
dot.node('A', 'Global Variables and Maze Initialization')
dot.node('B', 'isValidMove Function')
dot.node('C', 'chooseAction Function')
dot.node('D', 'updateQValues Function')
dot.node('E', 'qLearning Function')
dot.node('F', 'main Function')

# Add edges
dot.edges(['AF', 'FE', 'EC', 'ED', 'CB', 'DB'])

dot.render('picture/code_structure.jpg', view=True)  # save as jpg and open for viewing
