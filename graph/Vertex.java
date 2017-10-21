package graph;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

/**
 * V�rtice
 * @author lucas
 *
 * @param <T> Tipo da informa��o do v�rtice
 */
public class Vertex<T> {

	private T datum;
	private boolean mark;
	private Map<Integer, Vertex<T>> connectedVertices;
	
	/**
	 * Construtor
	 * @param datum Informa��o a ser guardada pelo v�rtice
	 */
	public Vertex(T datum) {
		this.datum = datum;
		this.mark = false;
		this.connectedVertices = new HashMap<Integer, Vertex<T>>();
	}
	
	/**
	 * Conectar o v�rtice a outro
	 * @param vertex O v�rtice com o qual este ser� conectado
	 */
	public void connectTo(Vertex<T> v) {
		this.connectedVertices.put(v.hashCode(), v);
	}
	
	/**
	 * Desconectar o v�rtice de outro
	 * @param vertex O v�rtice do qual este ser� desconectado
	 */
	public void disconnectFrom(Vertex<T> v) {
		this.connectedVertices.remove(v.hashCode());
	}
	
	/**
	 * Verificar se o v�rtice est� conectado � outro
	 * @param v O v�rtice a ser verificado
	 * @return true se h� uma conex�o entre os v�rtices
	 */
	public boolean isConnectedTo(Vertex<T> v) {
		return this.connectedVertices.containsKey(v.hashCode());
	}
	
	/**
	 * Obter os v�rtices adjacentes
	 * @return Cole��o de v�rtices adjacentes
	 */
	public Collection<Vertex<T>> getAdjacents() {
		return this.connectedVertices.values();
	}
	
	/**
	 * Obter o grau do v�rtice
	 * @return N�mero de arestas que incidem sobre o v�rtice
	 */
	public int getDegree() {
		return this.connectedVertices.size();
	}
	
	/**
	 * Obter a informa��o guardada pelo v�rtice
	 * @return A informa��o
	 */
	public T getDatum() {
		return this.datum;
	}
	
	/**
	 * Marcar o v�rtice
	 */
	public void mark() {
		this.mark = true;
	}
	
	/**
	 * Desmarcar o v�rtice
	 */
	public void clearMark() {
		this.mark = false;
	}
	
	/**
	 * Verificar se o v�rtice est� marcado
	 * @return true se o v�rtice est� marcado
	 */
	public boolean isMarked() {
		return this.mark;
	}
	
	/**
	 * Obter o fecho transitivo do v�rtice
	 * @return Cole��o de v�rtices alcan��veis a partir desse
	 */
	public Collection<Vertex<T>> getTransitiveClosure() {
		Collection<Vertex<T>> result = new ArrayList<Vertex<T>>();
		Collection<Vertex<T>> visited = new ArrayList<Vertex<T>>();
		
		this.getTransitiveClosure(this, result, visited);
		return result;
	}
	
	/**
	 * (M�todo auxiliar) Obter o fecho transitivo do v�rtice
	 * @param currentVertex V�rtice atual
	 * @param result Cole��o de v�rtices alcan��veis a partir desse
	 * @param visited Cole��o de v�rtices visitados
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
	 * Verificar igualdade entre v�rtices
	 * @param obj Objeto a ser verificado
	 * @return true se obj e esse v�rtice s�o iguais
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
