package graph;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

/**
 * Grafo
 * @author lucas
 *
 * @param <T> Tipo da informa��o dos v�rtices
 */
public class Graph<T> {

	private Map<Integer, Vertex<T>> vertices;

	/**
	 * Construtor
	 */
	public Graph() {
		this.vertices = new HashMap<Integer, Vertex<T>>();
	}

	/**
	 * Adicionar um v�rtice
	 * @param v O v�rtice a ser adicionado
	 */
	public void addVertex(Vertex<T> v) {
		this.vertices.put(v.hashCode(), v);
	}

	/**
	 * Remover um v�rtice
	 * @param v O v�rtice a ser removido
	 * @return O v�rtice removido ou null caso o v�rtice n�o esteja no grafo
	 */
	public Vertex<T> removeVertex(Vertex<T> v) {
		for(Vertex<T> adj : v.getAdjacents())
			adj.disconnectFrom(v);
		
		return this.vertices.remove(v.hashCode());
	}

	/**
	 * Conectar dois v�rtices
	 * @param v1 Um v�rtice a ser conectado
	 * @param v2 Um v�rtice a ser conectado
	 */
	public void connect(Vertex<T> v1, Vertex<T> v2) {
		v1.connectTo(v2);
		v2.connectTo(v1);
	}
	
	/**
	 * Desconectar dois v�rtices
	 * @param v1 Um v�rtice a ser desconectado
	 * @param v2 Um v�rtice a ser desconectado
	 */
	public void disconnect(Vertex<T> v1, Vertex<T> v2) {
		v1.disconnectFrom(v2);
		v2.disconnectFrom(v1);
	}

	/**
	 * Obter a ordem do grafo
	 * @return N�mero de v�rtices do grafo
	 */
	public int order() {
		return this.vertices.size();
	}
	
	/**
	 * Obter os v�rtices do grafo
	 * @return Cole��o de v�rtices do grafo
	 */
	public Collection<Vertex<T>> getVertices() {
		return this.vertices.values();
	}
	
	/**
	 * Obter um v�rtice qualquer
	 * @return Um v�rtice
	 */
	public Vertex<T> getRandomVertex() {
		ArrayList<Vertex<T>> v = new ArrayList<Vertex<T>>(this.getVertices());
		Random r = new Random(Calendar.getInstance().getTimeInMillis());
		
		return v.get(Math.abs(r.nextInt()) % v.size());
	}
	
	/**
	 * Verificar se o grafo � conexo
	 * @return true caso o grafo seja conexo
	 */
	public boolean isConnected() {
		ArrayList<Vertex<T>> tClosure = new ArrayList<Vertex<T>>(
										this.getRandomVertex().getTransitiveClosure());
		ArrayList<Vertex<T>> vertices = new ArrayList<Vertex<T>>(this.vertices.values());
		
		for( Vertex<T> v : vertices) {
			if(!tClosure.contains(v))
				return false;
		}
		
		return true;
	}

	/**
	 * Desmarcar todos os v�rtices do grafo
	 */
	public void clearVerticesMark() {
		for(Vertex<T> v : this.vertices.values())
			v.clearMark();
	}
	
	/**
	 * Verificar se o grafo possui algum ciclo
	 * @return true se o grafo possui pelo menos um ciclo
	 */
	public boolean hasCicle() {
		ArrayList<Vertex<T>> unvisited = new ArrayList<Vertex<T>>(this.vertices.values());
		boolean hasCicle = false;
		
		this.clearVerticesMark();
		
		while(!unvisited.isEmpty() && !hasCicle)
			hasCicle = this.hasCicle(unvisited.get(0), unvisited.get(0), unvisited);
		
		this.clearVerticesMark();
		return hasCicle;
	}
	
	/**
	 * (M�todo auxiliar) Verificar se o grafo possui algum ciclo
	 * @param previousV V�rtice anterior
	 * @param currentV V�rtice atual
	 * @return true se o grafo possui algum ciclo
	 */
	private boolean hasCicle(Vertex<T> previousV, Vertex<T> currentV,
							 ArrayList<Vertex<T>> unvisited) {
		if(currentV.isMarked())
			return true;
		
		currentV.mark();
		unvisited.remove(currentV);
		
		for(Vertex<T> adj : currentV.getAdjacents()) {
			if(!adj.equals(previousV)) {
				if(this.hasCicle(currentV, adj, unvisited))
					return true;
			}
		}
		
		currentV.clearMark();
		return false;
	}

}
