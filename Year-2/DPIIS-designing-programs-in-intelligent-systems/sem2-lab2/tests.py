# create table
# table = Table("main")
# fill table
"""    table.column_add("int", "id")
table.column_add("str", "name")
table.column_add("int", "age")
table.column_add("int", "gender")
table.column_add("str", "address")
table.record_add((0, "admin", 10, 2, "pushkina dom kolotushkina"))
table.record_add((1, "moderator1", 40, 1, "baker street 221b"))
table.record_add((2, "moderator2", 35, 2, "baker street 221a"))
table.record_add((3, "moderator3", 30, 1, "baker street 222b"))
table.record_add((4, "moderator4", 25, 1, "baker street 222a"))
# print table
table.print()
# save current info
table.save_to_xml()
# remove elements
table.column_add("str", "lol")
table.column_add("int", "zero")
table.column_remove("age")
table.column_remove("id")
table.record_remove(table.records[0])
table.record_remove(table.records[2])
# print table
table.print()
# load info
table.load_from_xml("main2.xml")
# print table
print("loaded:")
table.print()
# remove elements
table.column_add("str", "lol")
table.column_add("int", "zero")
table.column_remove("age")
table.column_remove("id")
table.record_remove(table.records[0])
table.record_remove(table.records[2])
# print table"""

# table.load_from_xml("main2.xml")
# table.print()

# table.record_remove(random.choice(table.records))
# for record in table.record_find("gender", 1):
#     print(record.elements)

# table.save_to_xml()
