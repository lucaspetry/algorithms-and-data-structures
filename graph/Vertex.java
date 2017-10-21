package graph;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

/**
 * Vértice
 * @author lucas
 *
 * @param <T> Tipo da informação do vértice
 */
public class Vertex<T> {

	private T datum;
	private boolean mark;
	private Map<Integer, Vertex<T>> connectedVertices;
	
	/**
	 * Construtor
	 * @param datum Informação a ser guardada pelo vértice
	 */
	public Vertex(T datum) {
		this.datum = datum;
		this.mark = false;
		this.connectedVertices = new HashMap<Integer, Vertex<T>>();
	}
	
	/**
	 * Conectar o vértice a outro
	 * @param vertex O vértice com o qual este será conectado
	 */
	public void connectTo(Vertex<T> v) {
		this.connectedVertices.put(v.hashCode(), v);
	}
	
	/**
	 * Desconectar o vértice de outro
	 * @param vertex O vértice do qual este será desconectado
	 */
	public void disconnectFrom(Vertex<T> v) {
		this.connectedVertices.remove(v.hashCode());
	}
	
	/**
	 * Verificar se o vértice está conectado à outro
	 * @param v O vértice a ser verificado
	 * @return true se há uma conexão entre os vértices
	 */
	public boolean isConnectedTo(Vertex<T> v) {
		return this.connectedVertices.containsKey(v.hashCode());
	}
	
	/**
	 * Obter os vértices adjacentes
	 * @return Coleção de vértices adjacentes
	 */
	public Collection<Vertex<T>> getAdjacents() {
		return this.connectedVertices.values();
	}
	
	/**
	 * Obter o grau do vértice
	 * @return Número de arestas que incidem sobre o vértice
	 */
	public int getDegree() {
		return this.connectedVertices.size();
	}
	
	/**
	 * Obter a informação guardada pelo vértice
	 * @return A informação
	 */
	public T getDatum() {
		return this.datum;
	}
	
	/**
	 * Marcar o vértice
	 */
	public void mark() {
		this.mark = true;
	}
	
	/**
	 * Desmarcar o vértice
	 */
	public void clearMark() {
		this.mark = false;
	}
	
	/**
	 * Verificar se o vértice está marcado
	 * @return true se o vértice está marcado
	 */
	public boolean isMarked() {
		return this.mark;
	}
	
	/**
	 * Obter o fecho transitivo do vértice
	 * @return Coleção de vértices alcançáveis a partir desse
	 */
	public Collection<Vertex<T>> getTransitiveClosure() {
		Collection<Vertex<T>> result = new ArrayList<Vertex<T>>();
		Collection<Vertex<T>> visited = new ArrayList<Vertex<T>>();
		
		this.getTransitiveClosure(this, result, visited);
		return result;
	}
	
	/**
	 * (Método auxiliar) Obter o fecho transitivo do vértice
	 * @param currentVertex Vértice atual
	 * @param result Coleção de vértices alcançáveis a partir desse
	 * @param visited Coleção de vértices visitados
	 */
	private void getTransitiveClosure(Vertex<T> currentVertex,
						Collection<Vertex<T>> result, Collection<Vertex<T>> visited) {
		
		visited.add(currentVertex);
		result.add(currentVertex);
		
		for( Vertex<T> v : currentVertex.getAdjacents()) {
			if(!visited.contains(v))
				this.getTransitiveClosure(v, result, visited);
		}

	}

	/**
	 * Verificar igualdade entre vértices
	 * @param obj Objeto a ser verificado
	 * @return true se obj e esse vértice são iguais
	 */
	@SuppressWarnings("unchecked")
	public boolean equals(Object obj) {
		if(obj instanceof Vertex) {
			Vertex<T> v = (Vertex<T>) obj;
			if(v.hashCode() == this.hashCode())
				return true;
		}
		
		return false;
	}
	
}
