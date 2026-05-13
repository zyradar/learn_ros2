from demo_python_pkg.ros2_person_node import PresonNode

class WriterNode(PresonNode):
    def __init__(self,name:str, age:int, book:str) -> None:
        print('WriterNode')
        super().__init__(name, age) # 调用父类init
        self.book = book

def main():
    node = WriterNode('san', 18, 'test')
    node.eat("fish")