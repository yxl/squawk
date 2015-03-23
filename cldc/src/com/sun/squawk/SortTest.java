/*
 * Copyright 2004-2010 Sun Microsystems, Inc. All Rights Reserved.
 * Copyright 2011 Oracle Corporation. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * only, as published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * Please contact Oracle Corporation, 500 Oracle Parkway, Redwood
 * Shores, CA 94065 or visit www.oracle.com if you need additional
 * information or have any questions.
 */

package com.sun.squawk;

public class SortTest {

    public static void main(String[] args) {
        sortTest();
        objectSortTest();
        nestedObjectSortTest();
    }

    static final int TOTAL_TIMES = 10;
    static void sortTest() {
        int[] data = new int[10000];
        int times = TOTAL_TIMES;
        long total = 0;
        while (times-- > 0) {
            for (int i = 0; i < data.length; i++) {
                data[i] = data.length - i;
            }
            long start = System.currentTimeMillis();
            doSort(data);
            long time = System.currentTimeMillis() - start;
            total += time;
            System.out.print(time + "ms ");
        }
        System.out.println();
        System.out.println("=== Simple sort: " + total / TOTAL_TIMES + "ms");
    }

    static void doSort(int[] a) {
        int t = 0;
        for (int i = 0; i < a.length - 1; i++) {
            for (int j = 0; j < a.length - 1 - i; j++) {
                if (a[j] > a[j + 1]) {
                    t = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = t;
                }
            }
        }
    }

    static class T {
        int v = 0;
    }

    static void objectSortTest() {
        T[] data = new T[10000];
        for (int i = 0; i < data.length; i++) {
            data[i] = new T();
        }
        int times = TOTAL_TIMES;
        long total = 0;
        while (times-- > 0) {
            for (int i = 0; i < data.length; i++) {
                data[i].v = data.length - i;
            }
            long start = System.currentTimeMillis();
            doObjectSort(data);
            long time = System.currentTimeMillis() - start;
            total += time;
            System.out.print(time + "ms ");
        }
        System.out.println();
        System.out.println("=== Object sort: " + total / TOTAL_TIMES + "ms");
    }

    static void doObjectSort(T[] a) {
        for (int i = 0; i < a.length - 1; i++) {
            for (int j = 0; j < a.length - 1 - i; j++) {
                if (a[j].v > a[j + 1].v) {
                    int t = a[j].v;
                    a[j].v = a[j + 1].v;
                    a[j + 1].v = t;
                }
            }
        }
    }

    static class N {
        T t = new T();
    }

    static void nestedObjectSortTest() {
        N[] data = new N[10000];
        for (int i = 0; i < data.length; i++) {
            data[i] = new N();
        }
        int times = TOTAL_TIMES;
        long total = 0;
        while (times-- > 0) {
            for (int i = 0; i < data.length; i++) {
                data[i].t.v = data.length - i;
            }
            long start = System.currentTimeMillis();
            doNestedObjectSort(data);
            long time = System.currentTimeMillis() - start;
            total += time;
            System.out.print(time + "ms ");
        }
        System.out.println();
        System.out.println("=== Nested object sort: " + total / TOTAL_TIMES + "ms");
    }

    static void doNestedObjectSort(N[] a) {
        for (int i = 0; i < a.length - 1; i++) {
            for (int j = 0; j < a.length - 1 - i; j++) {
                if (a[j].t.v > a[j + 1].t.v) {
                    int t = a[j].t.v;
                    a[j].t.v = a[j + 1].t.v;
                    a[j + 1].t.v = t;
                }
            }
        }
    }

    private SortTest() {
    }
}