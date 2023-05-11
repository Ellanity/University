from SPARQLWrapper import SPARQLWrapper, JSON

# set up a SPARQL endpoint for the Virtuoso repository
sparql = SPARQLWrapper("http://localhost:8890/sparql")

ontology_graph_name = "http://www.semanticweb.org/eldar/ontologies/2023/1/folklore-merged"


# set the query string
def new_query(query_string_got):
    standard_query_prefixes = f"""
    PREFIX owl: <http://www.w3.org/2002/07/owl#>
    PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
    PREFIX folklore: <http://www.semanticweb.org/eldar/ontologies/2023/1/folklore#>
    """
    query_created = f"""
    {standard_query_prefixes}
    {query_string_got}
    """
    return query_created

# query = new_query("SELECT * WHERE {?p ?o :s }")
query = new_query("""SELECT ?entity
WHERE {
  ?entity a ?class .
  FILTER(STRSTARTS(STR(?entity), STR(folklore:)))
} LIMIT 10""")

# set the query type to SELECT and return results as JSON
sparql.setQuery(query)
sparql.setReturnFormat(JSON)

# execute the query and parse the results
results = sparql.query().convert()

# iterate over the results and display them
for result in results["results"]["bindings"]:
    print(result)
