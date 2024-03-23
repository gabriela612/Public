package org.example.service.grafuri;

import org.example.domain.Entity;

import java.util.List;
import java.util.Map;
import java.util.function.Function;

@FunctionalInterface
public interface ParcurgereComponentaConexa {
    public abstract int parcurge(Entity<Long> inceput, List<Entity<Long>> all, Map<Long, Boolean> vizitati,
                                 Function<Entity<Long>, List<Entity<Long>>> getVecini);
}
