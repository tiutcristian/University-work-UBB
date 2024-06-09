from collections import deque


def topological_sort(activities_list, prerequisites_list):
    in_degree = {u: 0 for u in activities_list}
    for u in prerequisites_list:
        in_degree[u] = len(prerequisites_list[u])

    queue = deque([u for u in activities_list if in_degree[u] == 0])
    topo_ordered = []

    while queue:
        u = queue.popleft()
        topo_ordered.append(u)
        for v in prerequisites_list.keys():
            if u in prerequisites_list[v]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    queue.append(v)

    if len(topo_ordered) == len(activities_list):
        return topo_ordered
    else:
        return None


def get_earliest_start_times(activities_list, prerequisites_list, topo_ordered):
    es = {u: 0 for u in activities_list}
    for u in topo_ordered:
        for vert in prerequisites_list[u]:
            es[u] = max(es[u], es[vert] + activities_list[vert])
    return es


def get_latest_start_times(activities_list, prerequisites_list, topo_ordered, t_time):
    ls = {u: t_time-activities_list[u] for u in activities_list}
    for u in reversed(topo_ordered):
        for vert in prerequisites_list[u]:
            ls[vert] = min(ls[vert], ls[u] - activities_list[vert])
    return ls


def print_topo_sort(activities_list, prerequisites_list):
    topo_order = topological_sort(activities_list, prerequisites_list)
    if topo_order is None:
        print("The graph is not a DAG.")
        exit()

    earliest_start = get_earliest_start_times(activities_list, prerequisites_list, topo_order)
    total_time = max(earliest_start[u] + activities_list[u] for u in activities_list)
    latest_start = get_latest_start_times(activities_list, prerequisites_list, topo_order, total_time)
    critical_activities = [u for u in activities_list if earliest_start[u] == latest_start[u]]

    print("Topological Order:", topo_order)
    print("Earliest Start Times:", earliest_start)
    print("Latest Start Times:", latest_start)
    print("Total Project Time:", total_time)
    print("Critical Activities:", critical_activities)
