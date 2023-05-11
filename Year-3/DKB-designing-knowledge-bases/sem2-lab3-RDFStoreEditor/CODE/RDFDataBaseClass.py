"""
# That is file of rdf "connector"
# to work with your ontology you need to change ontology iris and graph name
# to words that are usually in the end of ontology name.
# Example:
# self.ontology_iri_short = "folklore"
# self.ontology_iri = "http://www.semanticweb.org/ontologies/2023/folklore#"
# self.ontology_graph_name = "http://www.semanticweb.org/eldar/ontologies/2023/1/folklore-merged"
"""

from SPARQLWrapper import SPARQLWrapper, JSON


class RDFDataBase:
    def __init__(self):
        # set up a SPARQL endpoint for the Virtuoso repository
        self.__sparql = SPARQLWrapper("http://localhost:8890/sparql")

        # ### ##### MAKE THIS UNIQUE ##### ### #
        self.ontology_iri_short = "folklore"
        self.ontology_iri = "http://www.semanticweb.org/eldar/ontologies/2023/1/folklore#"
        self.ontology_graph_name = "http://www.semanticweb.org/eldar/ontologies/2023/1/folklore-merged"

    def executeRDFQuery(self, query, query_method):
        # add prefixes
        query = self.preprocess_query(query)
        self.__sparql.setMethod(query_method)
        # set the query type to SELECT and return results as JSON
        self.__sparql.setQuery(query)
        self.__sparql.setReturnFormat(JSON)

        # execute the query and parse the results
        results = None
        try:
            results = self.__sparql.query().convert()
        except Exception as ex:
            print(f"Exception. Can't execute query. {ex}")
        if results is not None:
            if query_method == "GET":
                try:
                    return results["results"]["bindings"]
                except Exception as _:
                    return results
            if query_method == "POST":
                return results
        return results

    # delete everything except of iris unique names
    def clearRDFQueryResponse(self, results, result_name_to_clear):
        cleared_results = []
        for result in results:
            res = result[result_name_to_clear]["value"]
            if "#" in res:
                cleared_results.append([res.split("#")[-1]])
            else:
                cleared_results.append([res.split("/")[-1]])
        return cleared_results

    def preprocess_query(self, query_string_got):
        # can add here any prefixes you need
        standard_query_prefixes = f"""
            PREFIX owl: <http://www.w3.org/2002/07/owl#>
            PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
            PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
            PREFIX {self.ontology_iri_short}: <{self.ontology_iri}>
        """
        # add prefixes to query
        query_created = f"""
        {standard_query_prefixes}
        {query_string_got}
        """
        return query_created

    def __del__(self):
        pass
