from graphviz import Digraph

dot = Digraph(comment='程序流程图', format='png', node_attr={'shape': 'box'})

dot.node('A', '开始')
dot.node('B', '输入学校数量、男子团体项目数量和女子团体项目数量')
dot.node('C', '输入各学校名称')
dot.node('D', '输入项目名称、参与性别及名次取法')
dot.node('E', '输入各项目名次及得分')
dot.node('F', '计算并记录各学校总分、男女团体分')
dot.node('G', '按学校编号排序并打印')
dot.node('H', '按学校总分排序并打印')
dot.node('I', '按男女团体总分排序并打印')
dot.node('J', '查询学校某项目得分')
dot.node('K', '查询项目前N名学校及得分')
dot.node('L', '结束')

dot.edges(['AB', 'BC', 'CD', 'DE', 'EF', 'FG', 'GH', 'HI', 'IJ', 'JK', 'KL'])

dot.render('program_flowchart', view=True)  # 输出为program_flowchart.png
