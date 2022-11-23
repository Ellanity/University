class ModelDiary:
    def __init__(self):
        self.tasks = [
            {"name": "Eat", "category": "Personal", "date": "14:44\n12:12:2022", "overdue": 1},
            {"name": "Sleep", "category": "Personal", "date": "23:00\n12:12:2022", "overdue": 0},
        ]

    def addTask(self, task):
        pass

    def changeTask(self, task_index: int, delete_task: bool, complete_task: bool,
                   name: str, category: str, date_finish: str, frequency: str):
        pass

    def getTask(self, task_index: int):
        pass

    def getAllTasks(self):
        return self.tasks

    def getAllTasksCategory(self, category: str):
        pass


class Task:
    def __init__(self):
        self.name: str = ""
        self.category: str = ""
        self.date_finish: str = ""
        self.frequency: str = ""
        self.to_delete: bool = False

    def getData(self):
        pass

    def getPerformanceStatus(self):
        pass

    def changeData(self, delete_task: bool, complete_task: bool,
                   name: str, category: str, date_finish: str, frequency: str):
        pass

    def _changeParameters(self, name: str, category: str, date_finish: str, frequency: str):
        pass

    def _complete(self):
        pass


class DateAndTimeManager:
    def __init__(self):
        self.elements_of_periodicity_patterns = []

    def checkCorrectnessOfPeriodicityPatterns(self, periodicity_patterns: str):
        pass

    def checkCorrectnessOfDateAndTime(self, date_and_time: str):
        pass

    def getPerformanceStatus(self, date_and_time_deadline: str):
        pass

    def getNearestDate(self, periodicity_patterns: str):
        pass

    def _getNearestDayOfWeek(self, day_of_week: str):
        pass

    def _getDateInDay(self):
        pass

    def _getDateInWeek(self):
        pass

    def _getDateInMonth(self):
        pass

    def _getDateInYear(self):
        pass
