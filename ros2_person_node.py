class PresonNode:
    def __init__(self, name_value:str, age_value:int) -> None:
        self.name = name_value
        self.age = age_value
        
    def eat(self, food_name: str):
        """
        方法：吃东西
        """
        print(f"{self.name}, {self.age}, {food_name}")

def main():
    node = PresonNode("san", 18)
    node.eat("fish")

