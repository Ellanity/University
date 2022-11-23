from Model import ModelDiary


class Controller:
    def __init__(self):
        self.__model = ModelDiary()
        query_results: list = []
        choice_result: int = -1

    def getDataFromModel(self):
        pass

    def setDataToModel(self):
        pass

    def rememberChoice(self, task_index_in_table: int):
        pass

    def addTask(self, name: str, category: str, date_finish: str, frequency: str):
        pass

    def changeTask(self, task_index_in_table: int, delete_task: bool, complete_task: bool,
                   name: str, category: str, date_finish: str, frequency: str):
        pass

    def getAllTasks(self):
        return self.__model.getAllTasks()

    def getAllTasksCategory(self, category: str):
        pass

    def getTask(self, task_index_in_table: int):
        pass
