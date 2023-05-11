"""
# Model get rdf connector, it has different methods to work with database.
# If you wanna use response cleaning, specifie value? that must be cleared
# Example: RDFDataBase.clearRDFQueryResponse(result_name_to_clear="value")
"""

from RDFDataBaseClass import RDFDataBase


class AppModel:
    def __init__(self):
        self.database = RDFDataBase()

    def getAllTriples(self, *args):
        _ = args
        query = f"""SELECT *
                    WHERE {{ 
                        GRAPH <{self.database.ontology_graph_name}> {{ ?first ?relation ?second }} 
                    }}"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            for result in results:
                results_cleared.append([result["first"]["value"].split("#")[-1],
                                        result["relation"]["value"].split("#")[-1],
                                        result["second"]["value"].split("#")[-1]])
        return results_cleared

    def deleteTriple(self, iri_first, iri_relation, iri_second, *args):
        _ = args

        prequery = f"""ASK WHERE {{
                            GRAPH <http://www.semanticweb.org/eldar/ontologies/2023/1/folklore-merged> {{
                                ?iri_first ?iri_relation ?iri_second .
                                FILTER(STRENDS(STR(?iri_first), "#{iri_first}") &&
                                STRENDS(STR(?iri_relation), "#{iri_relation}") &&
                                STRENDS(STR(?iri_second), "#{iri_second}")) .
                            }}
                        }}"""
        prequery_result = self.database.executeRDFQuery(query=prequery, query_method="GET")
        if prequery_result["boolean"] is False:
            raise Exception(f"Can't find triple class {iri_first} - {iri_relation} - {iri_second}")

        query = f"""DELETE WHERE {{
                            GRAPH <http://www.semanticweb.org/eldar/ontologies/2023/1/folklore-merged> {{
                                ?iri_first ?iri_relation ?iri_second .
                                FILTER(STRENDS(STR(?iri_first), "#{iri_first}") &&
                                STRENDS(STR(?iri_relation), "#{iri_relation}") &&
                                STRENDS(STR(?iri_second), "#{iri_second}")) .
                            }}
                        }}"""
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]
            """for result in results:
                results_cleared.append([result["iri_first"]["value"].split("#")[-1],
                                        result["iri_relation"]["value"].split("#")[-1],
                                        result["iri_second"]["value"].split("#")[-1]])"""
        return results_cleared

    def addTriple(self, iri_first, iri_relation, iri_second, *args):
        _ = args
        if not self.checkClassExists(iri_first) and not self.checkIndividualExists(iri_first):
            raise Exception(f"Can't find class or individual {iri_first}")
        if not self.checkClassExists(iri_second) and not self.checkIndividualExists(iri_second):
            raise Exception(f"Can't find class or individual {iri_second}")
        relation_full_iri = self.__checkIriIsProperty(iri_relation)
        if relation_full_iri is None:
            raise Exception(f"Can't find relation {iri_relation}")

        query = f"""INSERT {{
                        GRAPH <{self.database.ontology_graph_name}> 
                        {{
                            {self.database.ontology_iri_short}:{iri_first} ?relation
                            {self.database.ontology_iri_short}:{iri_second} .
                        }} 
                    }}
                    WHERE {{
                        ?relation rdf:type <{relation_full_iri}> .
                        FILTER (STRENDS(STR(?relation), "{iri_relation}")) .
                    }}"""
        # print(query, relation_full_iri)
        # results = None
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]
        return results_cleared

    # ### ##### INDIVIDUALS METHODS ##### ### #
    def checkIndividualExists(self, individual_iri, *args):
        _ = args
        query = f"""ASK {{ {self.database.ontology_iri_short}:{individual_iri} rdf:type owl:NamedIndividual}}"""
        query_result = self.database.executeRDFQuery(query=query, query_method="GET")
        if query_result["boolean"] is False:
            return False
        return True

    def getIndividualsAll(self, *args):
        _ = args
        query = f"""SELECT ?individual ?class
                    WHERE {{
                        GRAPH <{self.database.ontology_graph_name}> {{
                            ?individual a ?class .
                            FILTER(STRSTARTS(STR(?class), STR({self.database.ontology_iri_short}:)))
                        }}
                    }} ORDER BY (STR(?individual))"""  # LIMIT 10"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            for result in results:
                results_cleared.append([result["individual"]["value"].split("#")[-1], result["class"]["value"].split("#")[-1]])
        return results_cleared

    def getIndividualsByClass(self, class_iri, *args):
        _ = args
        query = f"""SELECT ?individual 
                    WHERE {{
                        GRAPH <{self.database.ontology_graph_name}> {{
                            ?individual a ?class .
                            FILTER(STRSTARTS(STR(?class), STR({self.database.ontology_iri_short}:{class_iri})))
                        }}
                    }} ORDER BY (STR(?individual))"""  # LIMIT 10"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            for result in results:
                results_cleared.append([result["individual"]["value"].split("#")[-1], class_iri])
        return results_cleared

    def addIndividualByClass(self, individual_iri, class_iri, *args):
        _ = args
        class_exists = self.checkClassExists(class_iri=class_iri)
        if class_exists is False:
            raise Exception(f"Can't find class {class_iri}")

        query = f"""INSERT {{
                        GRAPH <{self.database.ontology_graph_name}> 
                        {{
                            {self.database.ontology_iri_short}:{individual_iri} 
                            rdf:type {self.database.ontology_iri_short}:{class_iri} .
                        }}
                    }} WHERE {{ }}"""
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]
        return results_cleared

    def updateIndividualIri(self, old_iri, new_iri, *args):
        _ = args
        query = f"""DELETE {{
                        GRAPH <{self.database.ontology_graph_name}> {{
                            <{self.database.ontology_iri_short}:{old_iri}> ?p ?o .
                            ?s ?p <{self.database.ontology_iri_short}:{old_iri}> .
                        }} 
                    }}
                    INSERT {{
                        GRAPH <{self.database.ontology_graph_name}> {{
                            <{self.database.ontology_iri_short}:{new_iri}> ?p ?o .
                            ?s ?p <{self.database.ontology_iri_short}:{new_iri}> .
                        }} 
                    }}
                    WHERE {{ 
                        GRAPH <{self.database.ontology_graph_name}> {{
                            {{ <{self.database.ontology_iri_short}:{old_iri}> ?p ?o . }}
                            UNION
                            {{ ?s ?p <{self.database.ontology_iri_short}:{old_iri}> . }}
                        }} 
                    }}"""
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]
        return results_cleared

    def deleteIndividualIri(self, individual_iri, *args):
        _ = args
        query = f"""
            DELETE {{ 
                GRAPH <{self.database.ontology_graph_name}> {{
                    {self.database.ontology_iri_short}:{individual_iri} ?p ?o .
                    ?s ?p {self.database.ontology_iri_short}:{individual_iri} .
                }} 
            }}
            WHERE {{ 
                GRAPH <{self.database.ontology_graph_name}> {{
                    {{ {self.database.ontology_iri_short}:{individual_iri} ?p ?o . }}
                    UNION
                    {{ ?s ?p {self.database.ontology_iri_short}:{individual_iri} . }}
                }} 
            }}
            """
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]
        return results_cleared

    # ### ##### CLASSES METHODS ##### ### #
    def checkClassExists(self, class_iri, *args):
        _ = args
        query = f"""ASK {{ {self.database.ontology_iri_short}:{class_iri} rdf:type owl:Class}}"""
        query_result = self.database.executeRDFQuery(query=query, query_method="GET")
        if query_result["boolean"] is False:
            return False
        return True

    def getClasses(self, *args):
        _ = args
        query = f"""SELECT ?ont_class
                    WHERE {{ 
                        GRAPH <{self.database.ontology_graph_name}> {{
                            ?ont_class rdf:type owl:Class .
                        }}
                    }} ORDER BY (STR(?ont_class))"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            for result in results:
                results_cleared.append([result["ont_class"]["value"].split("#")[-1]])
        return results_cleared

    def addClass(self, class_iri, *args):
        _ = args
        query = f"""INSERT {{
                        GRAPH <{self.database.ontology_graph_name}> 
                            {{
                                {self.database.ontology_iri_short}:{class_iri} 
                                rdf:type owl:Class.
                            }}
                        }} WHERE {{ }}"""
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]
        return results_cleared

    def updateClass(self, new_iri, old_iri, *args):
        _ = args
        query = f"""DELETE {{
                        GRAPH <{self.database.ontology_graph_name}> {{
                            {self.database.ontology_iri_short}:{old_iri} ?p ?o .
                            ?s ?p {self.database.ontology_iri_short}:{old_iri} .
                        }} 
                    }}
                    INSERT {{
                        GRAPH <{self.database.ontology_graph_name}> {{
                            {self.database.ontology_iri_short}:{new_iri} ?p ?o .
                            ?s ?p {self.database.ontology_iri_short}:{new_iri} .
                            #{self.database.ontology_iri_short}:{new_iri} rdf:type owl:Class .
                        }} 
                    }}
                    WHERE {{ 
                        GRAPH <{self.database.ontology_graph_name}> {{
                            {{ {self.database.ontology_iri_short}:{old_iri} ?p ?o . }}
                            UNION
                            {{ ?s ?p {self.database.ontology_iri_short}:{old_iri} . }}
                            UNION 
                            {{ {self.database.ontology_iri_short}:{old_iri} rdf:type owl:Class .}}
                        }} 
                    }}"""
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        # print(results)
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]
        return results_cleared

    def deleteClass(self, class_iri, *args):
        _ = args
        # delete all triples with individuals of this classes???
        query = f"""DELETE {{ 
                        GRAPH <{self.database.ontology_graph_name}> {{
                            {self.database.ontology_iri_short}:{class_iri} ?p ?o .
                            ?s ?p {self.database.ontology_iri_short}:{class_iri} .
                        }} 
                    }}
                    WHERE {{ 
                        GRAPH <{self.database.ontology_graph_name}> {{
                            {{ {self.database.ontology_iri_short}:{class_iri} ?p ?o . }}
                            UNION
                            {{ ?s ?p {self.database.ontology_iri_short}:{class_iri} . }}
                            UNION 
                            {{ {self.database.ontology_iri_short}:{class_iri} rdf:type owl:Class .}}
                        }} 
                    }}"""
        results = self.database.executeRDFQuery(query=query, query_method="POST")
        results_cleared = []
        if results is not None:
            results_cleared = results["results"]["bindings"][0]["callret-0"]["value"]

        return results_cleared

    # ### ##### DATA PROPERTIES METHODS ##### ### #
    def checkDataPropertyExists(self, data_iri, *args):
        _ = args
        type_of_property = "owl:DatatypeProperty"
        return self.__checkPropertyExists(property_iri=data_iri, type_of_property=type_of_property)

    def getDataPropertiesAll(self, *args):
        _ = args
        value_to_get = "data_property"
        type_of_property = "owl:DatatypeProperty"
        return self.__getProperties(value_to_get=value_to_get, type_of_property=type_of_property)

    def addDataProperty(self, *args):
        _ = args

    def updateDataProperty(self, *args):
        _ = args

    def deleteDataProperty(self, *args):
        _ = args

    # ### ##### OBJECT PROPERTIES METHODS ##### ### #
    def checkObjectPropertyExists(self, object_iri, *args):
        _ = args
        type_of_property = "owl:ObjectProperty"
        return self.__checkPropertyExists(property_iri=object_iri, type_of_property=type_of_property)

    def getObjectPropertiesAll(self, *args):
        _ = args
        value_to_get = "object_property"
        type_of_property = "owl:ObjectProperty"
        return self.__getProperties(value_to_get=value_to_get, type_of_property=type_of_property)

    def addObjectProperty(self, *args):
        _ = args

    def updateObjectProperty(self, *args):
        _ = args

    def deleteObjectProperty(self, *args):
        _ = args

    # ### ##### ANNOTATION PROPERTIES METHODS ##### ### #
    def checkAnnotationPropertyExists(self, annotation_iri, *args):
        _ = args
        type_of_property = "owl:AnnotationProperty"
        return self.__checkPropertyExists(property_iri=annotation_iri,
                                          type_of_property=type_of_property, only_in_graph=False)

    def getAnnotationPropertiesAll(self, *args):
        _ = args
        value_to_get = "annotation_property"
        type_of_property = "owl:AnnotationProperty"
        return self.__getProperties(value_to_get=value_to_get, type_of_property=type_of_property, only_in_graph=False)

    def addAnnotationProperty(self, *args):
        _ = args

    def updateAnnotationProperty(self, *args):
        _ = args

    def deleteAnnotationProperty(self, *args):
        _ = args

    # ### ##### DATATYPES PROPERTIES METHODS ##### ### #
    def checkDatatypeExists(self, datatype_iri, *args):
        _ = args
        type_of_property = "rdf:Property"
        return self.__checkPropertyExists(property_iri=datatype_iri,
                                          type_of_property=type_of_property, only_in_graph=False)

    def getDatatypesAll(self, *args):
        _ = args
        value_to_get = "datatypes"
        type_of_property = "rdf:Property"
        return self.__getProperties(value_to_get=value_to_get,
                                    type_of_property=type_of_property, only_in_graph=False)

    def addDatatype(self, *args):
        _ = args

    def updateDatatype(self, *args):
        _ = args

    def deleteDatatype(self, *args):
        _ = args

    # ### ##### COMMON FOR PROPERTIES ##### ### #
    def __checkPropertyExists(self, property_iri, type_of_property, only_in_graph=True, *args):
        _ = args
        query = ""
        if only_in_graph:
            query = f"""ASK WHERE {{
                            GRAPH <{self.database.ontology_graph_name}> {{
                                ?relation rdf:type {type_of_property} .
                                FILTER (STRENDS(STR(?relation), "{property_iri}")) .
                            }}
                        }}"""
        else:
            query = f"""ASK WHERE {{
                            ?relation rdf:type {type_of_property} .
                            FILTER (STRENDS(STR(?relation), "{property_iri}")) .
                        }}"""

        query_result = self.database.executeRDFQuery(query=query, query_method="GET")
        if query_result["boolean"] is False:
            return False
        return True

    def __getProperties(self, value_to_get, type_of_property, only_in_graph=True, *args):
        _ = args
        query = ""
        if only_in_graph:
            query = f"""
                SELECT ?{value_to_get}
                WHERE {{ 
                    GRAPH <{self.database.ontology_graph_name}> {{
                        ?{value_to_get} rdf:type {type_of_property} . 
                    }} 
                }} ORDER BY (STR(?{value_to_get}))"""
        else:
            query = f"""
                SELECT ?{value_to_get}
                WHERE {{ 
                    ?{value_to_get} rdf:type {type_of_property} . 
                }} ORDER BY (STR(?{value_to_get}))"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            results_cleared = self.database.clearRDFQueryResponse(results=results, result_name_to_clear=value_to_get)
        return results_cleared

    def __checkIriIsProperty(self, iri):
        query = f"""SELECT DISTINCT ?predicate WHERE {{?subject ?predicate ?object .}}"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []

        if results is not None:
            results_cleared = self.database.clearRDFQueryResponse(results=results, result_name_to_clear="predicate")

        for index in range(len(results_cleared)):
            # if [iri] in results_cleared:
            if iri in results_cleared[index]:
                return results[index]["predicate"]["value"]
        return None

    """
    Template if you wanna add any entities 
    # ### ##### SMTH METHODS ##### ### #
    def getSmths(self, *args):
        _ = args

    def addSmth(self, *args):
        _ = args

    def updateSmth(self, *args):
        _ = args

    def deleteSmth(self, *args):
        _ = args
    """

    # ### ##### SPECIAL QUERIES ##### ### #
    def specialQueryFirst(self, *args):
        starts_from = str(args[0][0].text)
        value_to_get = "vertex"
        query = f"""SELECT ?{value_to_get} WHERE {{
                        {{?{value_to_get} ?relation ?object .}}
                        UNION
                        {{?subject ?{value_to_get} ?object .}}
                        UNION
                        {{?subject ?relation ?{value_to_get} .}}
                        BIND (
                            STRSTARTS (
                                (STRAFTER(STR(?{value_to_get}), STR("#"))),
                                STR("{starts_from}")
                            )
                        AS ?x)
                        FILTER (?x = true)
            }}"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            results_cleared = self.database.clearRDFQueryResponse(results=results, result_name_to_clear=value_to_get)
        return results_cleared

    def specialQuerySecond(self, *args):
        vertex_name = str(args[0][0].text)
        value_to_get = "vertex"
        query = f"""SELECT * WHERE {{
                            ?subject ?relation {self.database.ontology_iri_short}:{vertex_name} .
            }}"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            for result in results:
                results_cleared.append([result["subject"]["value"].split("#")[-1],
                                        result["relation"]["value"].split("#")[-1], vertex_name])
        return results_cleared

    def specialQueryThird(self, *args):
        subject = str(args[0][0].text.split(',')[0])
        object = str(args[0][0].text.split(',')[1])
        query = f"""SELECT * WHERE {{
                            folklore:{subject} ?relation folklore:{object} .
            }}"""
        results = self.database.executeRDFQuery(query=query, query_method="GET")
        results_cleared = []
        if results is not None:
            for result in results:
                results_cleared.append([subject, result["relation"]["value"].split("#")[-1], object])
        return results_cleared
